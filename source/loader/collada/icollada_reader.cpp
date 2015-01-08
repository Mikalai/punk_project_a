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
		float_array,
		param,
		accessor
	};

	enum class ColladaAttribute {
		bad, 
		id, 
		name, 
		count,
		sid,
		type,
		semantic,
		source,
		offset,
		stride
	};

	std::pair<const char*, ColladaKeyword> collada_mapping[] {
		{ "float_array", ColladaKeyword::float_array },
		{ "param", ColladaKeyword::param },
		{ "accessor", ColladaKeyword::accessor }
	};

	std::pair<const char*, ColladaAttribute> collada_attribute_mapping[] {
		{ "id", ColladaAttribute::id },
		{ "name", ColladaAttribute::name },
		{ "count", ColladaAttribute::count },
		{ "sid", ColladaAttribute::sid },
		{ "type", ColladaAttribute::type },
		{ "semantic", ColladaAttribute::semantic },
		{ "source", ColladaAttribute::source },
		{ "offset", ColladaAttribute::offset },
		{ "stride", ColladaAttribute::stride }
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

	Attributes::ParamType ParseColladaType(const char* value) {
		if (!strcmp(value, "float"))
			return Attributes::ParamType::Float;
		if (!strcmp(value, "int"))
			return Attributes::ParamType::Int;
		return Attributes::ParamType::Bad;
	}

	Attributes::ParamSemantic ParseColladaSemantic(const char* value) {
		return Attributes::ParamSemantic::Bad;
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
				m_current_frame->Begin(key);
			}
			else {
				switch (key)
				{
				case ColladaKeyword::float_array:
					m_current_frame.reset(new FloatArrayFrame{ [this](Attributes::IFloatArrayPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::param:
					m_current_frame.reset(new ParamFrame{ [this](Attributes::IParamPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::accessor:
					m_current_frame.reset(new AccessorFrame{ [this](Attributes::IAccessorPtr& value) {
						m_result = value;
					} });
					break;
				default:
					throw Error::LoaderException{ Core::String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
				}
			}
		}

		void End(ColladaKeyword key) {
			if (m_current_frame.get()) {
				if (m_current_frame->End())
					m_current_frame.reset(nullptr);
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

		//
		//	BaseFrame
		//
		class BaseFrame {
		public:
			virtual ~BaseFrame() {}
			virtual void Attribute(ColladaAttribute attribute, const char* value) {}
			virtual void Text(const char* text, int len) {}
			virtual void Begin(ColladaKeyword key) {}
			virtual bool End() { return true; }
		};

		//
		//	FloatArrayFrame
		//
		class FloatArrayFrame : public BaseFrame {
		public:
			FloatArrayFrame(std::function<void(Core::Pointer<Attributes::IFloatArray>&)> on_end)
				: m_float_array{ System::CreateInstancePtr<Attributes::IFloatArray>(Attributes::CLSID_FloatArray, Attributes::IID_IFloatArray) }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {}

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

			bool End() override {
				if (m_on_end) {
					m_on_end(m_float_array);
				}
				return true;
			}

		private:			
			Attributes::IFloatArrayPtr m_float_array;
			std::function<void(Attributes::IFloatArrayPtr&)> m_on_end;			
		};

		//
		//	ParamFrame
		//
		class ParamFrame : public BaseFrame {
		public:
			ParamFrame(std::function<void(Attributes::IParamPtr&)> on_end)
				: m_value{ System::CreateInstancePtr<Attributes::IParam>(Attributes::CLSID_Param, Attributes::IID_IParam) }
				, m_on_end{ on_end }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				switch (attribute)
				{
				case ColladaAttribute::name:
					m_value->SetName(value);
					break;
				case ColladaAttribute::sid:
					m_value->SetSid(value);
					break;
				case ColladaAttribute::type:
					m_value->SetType(ParseColladaType(value));
					break;
				case ColladaAttribute::semantic:
					m_value->SetSemantic(ParseColladaSemantic(value));
				default:
					throw Error::LoaderException(Core::String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				return true;
			}

		private:
			Attributes::IParamPtr m_value;
			std::function<void(Attributes::IParamPtr&)> m_on_end;
		};

		//
		//	AccessorFrame
		//
		class AccessorFrame : public BaseFrame {
		public:
			AccessorFrame(std::function<void(Attributes::IAccessorPtr&)> on_end)
				: m_value{ System::CreateInstancePtr<Attributes::IAccessor>(Attributes::CLSID_Accessor, Attributes::IID_IAccessor) }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case Punk::Engine::IoModule::ColladaKeyword::param:
						m_current_frame.reset(new ParamFrame{ [this](Attributes::IParamPtr& value) {
							m_value->AddParam(value);
						} });
						break;
					default:
						throw Error::LoaderException{ Core::String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
					}
				}
			}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (m_current_frame)
					m_current_frame->Attribute(attribute, value);
				else {
					switch (attribute)
					{
					case ColladaAttribute::source:
						m_value->SetSource(value);
						break;
					case ColladaAttribute::offset:
						m_value->SetOffset(Core::String(value).ToInt32());
						break;
					case ColladaAttribute::stride:
						m_value->SetStride(Core::String(value).ToInt32());
						break;
					case ColladaAttribute::count:
						m_value->SetCount(Core::String(value).ToInt32());
						break;
					default:
						throw Error::LoaderException(Core::String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
					}
				}
			}

			void Text(const char* text, int len) override {
				if (m_current_frame)
					m_current_frame->Text(text, len);
			}

			bool End() {
				if (m_current_frame) {
					if (m_current_frame->End())
						m_current_frame.reset();
					return false;
				}
				else {
					if (m_on_end)
						m_on_end(m_value);
					return true;
				}
			}

		private:
			std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
			Core::Pointer<Attributes::IAccessor> m_value;
			std::function<void(Core::Pointer<Attributes::IAccessor>&)> m_on_end;
		};
		//
		//	SourceFrame
		//
		/*class SourceFrame : public BaseFrame {
		public:

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (m_current_frame.get()) {
					m_current_frame->Attribute(attribute, value);
				}
				else {
					switch (attribute)
					{
					case ColladaAttribute::id:
						break;
					case ColladaAttribute::name:
						break;
					default:
						throw Error::LoaderException(Core::String("Unexpected attribute {0}", ParseAttribute(attribute)));
					}
				}
			}

			void Text(const char* text, int len) override {
				if (m_current_frame) {
					m_current_frame->Text(text, len);
				}
			}
			
			void Begin(ColladaKeyword key) override {
				switch (key)
				{
				case ColladaKeyword::bad:
					break;
				case ColladaKeyword::float_array:
					break;
				default:
					throw Error::LoaderException{ Core::String("Unexpected keyword {0}").arg(Parse(key)) };
				}
			}
			
			void End() override {
			}

		private:
			std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		};*/

		std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		Core::Pointer<Core::IObject> m_result{ Core::make_ptr((Core::IObject*)nullptr) };

		std::atomic<std::uint32_t> m_ref_count{ 0 };		
	};


	PUNK_REGISTER_CREATOR(CLSID_ColladaReader, (System::CreateInstance<ColladaReader, IReader>));
}
PUNK_ENGINE_END
