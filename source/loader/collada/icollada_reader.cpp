#include <stack>
#include <functional>
#include <loader/ireader.h>
#include <loader/error/loader_error.h>
#include <expat/expat.h>
#include <string/buffer.h>
#include <string/string.h>
#include <string/string_list.h>
#include <system/filesystem/module.h>
#include <system/factory/module.h>
#include <attributes/data_flow/module.h>

PUNK_ENGINE_BEGIN
namespace IoModule {

	enum class ColladaKeyword {
		bad,
		float_array
	};

	enum class ColladaAttribute {
		bad, 
		id, 
		name, 
		count
	};

	std::pair<const char*, ColladaKeyword> collada_mapping[] {
		{"float_array", ColladaKeyword::float_array}
	};

	std::pair<const char*, ColladaAttribute> collada_attribute_mapping[] {
		{ "id", ColladaAttribute::id },
		{ "name", ColladaAttribute::name },
		{ "count", ColladaAttribute::count }
	};

	ColladaKeyword Parse(const char* value) {
		for (int i = 0; i < _countof(collada_mapping); ++i) {
			if (!strcmp(collada_mapping[i].first, value)) {
				return collada_mapping[i].second;
			}
		}
		return ColladaKeyword::bad;
	}

	const char* Parse(ColladaKeyword  value) {
		for (int i = 0; i < _countof(collada_mapping); ++i) {
			if (collada_mapping[i].second == value) {
				return collada_mapping[i].first;
			}
		}
		return "[ERROR]";
	}

	ColladaAttribute ParseAttribute(const char* value) {
		for (int i = 0; i < _countof(collada_attribute_mapping); ++i) {
			if (!strcmp(collada_attribute_mapping[i].first, value)) {
				return collada_attribute_mapping[i].second;
			}
		}
		return ColladaAttribute::bad;
	}

	const char* ParseAttribute(ColladaAttribute value) {
		for (int i = 0; i < _countof(collada_attribute_mapping); ++i) {
			if (collada_attribute_mapping[i].second == value) {
				return collada_attribute_mapping[i].first;
			}
		}
		return "[ERROR]";
	}

	class ColladaReader : public IReader {
	public:
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;

			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (IReader*) this;
				AddRef();
			}
			else if (type == IID_IReader) {
				*object = this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IReader
		Core::Pointer<Core::IObject> Read(const Core::String& filename)  override {
			Core::Buffer buffer;
			System::BinaryFile::Load(filename, buffer);
			return Read(buffer);
		}

		Core::Pointer<Core::IObject> Read(Core::Buffer& buffer) override {

			auto parser = XML_ParserCreate(nullptr);

			XML_SetElementHandler(parser, Start, End);			
			XML_SetCharacterDataHandler(parser, Data);
			XML_SetUserData(parser, this);

			while (!buffer.IsEnd()) {
				auto s = buffer.ReadString();
				auto data = (char*)s.Data();
				auto size = s.Size();

				if (XML_Parse(parser, data, size, buffer.IsEnd()) == XML_STATUS_ERROR) {
					auto s = Core::String("Parse error at line {0}: {1}").arg((int)XML_GetCurrentLineNumber(parser)).arg(XML_ErrorString(XML_GetErrorCode(parser)));
					throw Error::LoaderException(s);
				}
			}

			return m_result;
		}

		static void XMLCALL Data(void *data, const char *el, int len) {
			ColladaReader* reader = (ColladaReader*)data;
			reader->Text(el, len);
		}

		static void XMLCALL Start(void *data, const char *el, const char **attr)
		{
			ColladaReader* reader = (ColladaReader*)data;

			auto cmd = Parse(el);
			reader->Begin(cmd);
			
			for (int i = 0; attr[i]; i += 2) {
				auto attribute = ParseAttribute(attr[i]);
				reader->Attribute(attribute, attr[i + 1]);
			}
		}

		static void XMLCALL End(void *data, const char *el)
		{
			ColladaReader* reader = (ColladaReader*)data;
			auto cmd = Parse(el);
			reader->End(cmd);
		}

		void Begin(ColladaKeyword key) {
			auto prev_frame = m_current_frame.get();
			if (m_current_frame.get()) {
				m_frames.push(std::move(m_current_frame));
			}
				
			switch (key)
			{
			case ColladaKeyword::float_array:
				m_current_frame.reset(new FloatArrayFrame{ [prev_frame, this] (Core::Pointer<Attributes::IFloatArray>& value) {
					if (prev_frame)
						prev_frame->ChildComplete(value);
					else {
						m_result = value;
					}
				} });
				break;
			default:
				throw Error::LoaderException{ Core::String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
			}
		}

		void End(ColladaKeyword key) {
			if (m_current_frame.get()) {
				m_current_frame->End();
			}
			m_current_frame.reset(nullptr);
			if (!m_frames.empty()) {
				m_current_frame = std::move(m_frames.top());
				m_frames.pop();				
			}
		}

		void Attribute(ColladaAttribute attribute, const char* value) {
			if (m_current_frame)
				m_current_frame->Attribute(attribute, value);
		}

		void Text(const char* text, int len) {
			if (m_current_frame)
				m_current_frame->Text(text, len);
		}

	private:

		class BaseFrame {
		public:
			virtual ~BaseFrame() {}
			virtual void Attribute(ColladaAttribute attribute, const char* value) = 0;
			virtual void Text(const char* text, int len) = 0;
			virtual void End() = 0;
			virtual void ChildComplete(Core::Pointer<Attributes::IFloatArray>& value) {}
		};

		class FloatArrayFrame : public BaseFrame {
		public:
			FloatArrayFrame(std::function<void(Core::Pointer<Attributes::IFloatArray>&)> on_end)
				: m_float_array{ System::CreateInstancePtr<Attributes::IFloatArray>(Attributes::CLSID_FloatArray, Attributes::IID_IFloatArray) }
				, m_on_end{ on_end }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				switch (attribute)
				{
				case ColladaAttribute::id:
					m_float_array->SetId(value);
					break;
				case ColladaAttribute::name:
					m_float_array->SetName(value);
					break;
				case ColladaAttribute::count:
					m_float_array->SetCount(Core::String{ value }.ToInt32());
					break;
				default:
					throw Error::LoaderException(Core::String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Text(const char* text, int len) override {
				Core::String s{ text, (std::uint32_t)len };
				auto values = s.Split(" ");
				float* data = (float*)m_float_array->Data();
				for (int i = 0, max_i = values.Size(); i < max_i; ++i) {
					auto v = values[i].ToFloat();
					data[i] = v;
				}
			}

			void End() override {
				if (m_on_end) {
					m_on_end(m_float_array);
				}
			}

		private:			
			Core::Pointer<Attributes::IFloatArray> m_float_array{ Core::make_ptr((Attributes::IFloatArray*)nullptr) };
			std::function<void(Core::Pointer<Attributes::IFloatArray>&)> m_on_end;			
		};

		std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		std::stack<std::unique_ptr<BaseFrame>> m_frames;
		Core::Pointer<Core::IObject> m_result{ Core::make_ptr((Core::IObject*)nullptr) };

		std::atomic<std::uint32_t> m_ref_count{ 0 };		
	};


	PUNK_REGISTER_CREATOR(CLSID_ColladaReader, (System::CreateInstance<ColladaReader, IReader>));
}
PUNK_ENGINE_END
