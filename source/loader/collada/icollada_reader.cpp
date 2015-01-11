#include <stack>
#include <core/pointer.h>
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
using namespace Core;
using namespace Attributes;
namespace IoModule {

	enum class ColladaKeyword {
		bad,
		float_array,
		param,
		accessor,
		technique_common,
		source,
		input
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
		{ "accessor", ColladaKeyword::accessor },
		{ "technique_common", ColladaKeyword::technique_common },
		{ "source", ColladaKeyword::source },
		{ "input", ColladaKeyword::input }
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
		{ "stride", ColladaAttribute::stride },
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

	ParamType ParseColladaType(const char* value) {
		if (!strcmp(value, "float"))
			return ParamType::Float;
		if (!strcmp(value, "int"))
			return ParamType::Int;
		return ParamType::Bad;
	}

	ParamSemantic ParseColladaSemantic(const char* value) {
		return ParamSemantic::Bad;
	}

	InputSemantic ParseInputSemantic(const char* value) {
		if (!strcmp(value, "POSITION"))
			return InputSemantic::Position;
		return InputSemantic::Bad;
	}

	class ColladaReader : public IReader {
	public:

		//	IObject
		void QueryInterface(const Guid& type, void** object) override {
			if (!object)
				return;

			*object = nullptr;
			if (type == IID_IObject) {
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
		Pointer<IObject> Read(const String& filename)  override {
			Buffer buffer;
			System::BinaryFile::Load(filename, buffer);
			return Read(buffer);
		}

		Pointer<IObject> Read(Buffer& buffer) override {

			auto parser = XML_ParserCreate(nullptr);

			XML_SetElementHandler(parser, Start, End);
			XML_SetCharacterDataHandler(parser, Data);
			XML_SetUserData(parser, this);

			while (!buffer.IsEnd()) {
				auto s = buffer.ReadString();
				auto data = (char*)s.Data();
				auto size = s.Size();

				if (XML_Parse(parser, data, size, buffer.IsEnd()) == XML_STATUS_ERROR) {
					auto s = String("Parse error at line {0}: {1}").arg((int)XML_GetCurrentLineNumber(parser)).arg(XML_ErrorString(XML_GetErrorCode(parser)));
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
					m_current_frame.reset(new FloatArrayFrame{ [this](IFloatArrayPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::param:
					m_current_frame.reset(new ParamFrame{ [this](IParamPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::accessor:
					m_current_frame.reset(new AccessorFrame{ [this](IAccessorPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::source:
					m_current_frame.reset(new SourceFrame{ [this](ISourcePtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::input:
					m_current_frame.reset(new InputFrame{ [this](IInputPtr& value) {
						m_result = value;
					} });
					break;
				default:
					throw Error::LoaderException{ String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
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
			FloatArrayFrame(std::function<void(Pointer<IFloatArray>&)> on_end)
				: m_float_array{ NewFloatArray() }
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
					m_float_array->SetCount(String{ value }.ToInt32());
					break;
				default:
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Text(const char* text, int len) override {
				String s{ text, (std::uint32_t)len };
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
			IFloatArrayPtr m_float_array{ nullptr };
			std::function<void(IFloatArrayPtr&)> m_on_end;
		};

		//
		//	ParamFrame
		//
		class ParamFrame : public BaseFrame {
		public:
			ParamFrame(std::function<void(IParamPtr&)> on_end)
				: m_value{ NewParam() }
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
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				return true;
			}

		private:
			IParamPtr m_value;
			std::function<void(IParamPtr&)> m_on_end;
		};

		//
		//	AccessorFrame
		//
		class AccessorFrame : public BaseFrame {
		public:
			AccessorFrame(std::function<void(IAccessorPtr&)> on_end)
				: m_value{ NewAccessor() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::param:
						m_current_frame.reset(new ParamFrame{ [this](IParamPtr& value) {
							m_value->AddParam(value);
						} });
						break;
					default:
						throw Error::LoaderException{ String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
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
						m_value->SetOffset(String(value).ToInt32());
						break;
					case ColladaAttribute::stride:
						m_value->SetStride(String(value).ToInt32());
						break;
					case ColladaAttribute::count:
						m_value->SetCount(String(value).ToInt32());
						break;
					default:
						throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
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
			Pointer<IAccessor> m_value;
			std::function<void(Pointer<IAccessor>&)> m_on_end;
		};

		//
		//	SourceFrame
		//
		class SourceFrame : public BaseFrame {
		public:

			SourceFrame(std::function<void(ISourcePtr&)> on_end)
				: m_on_end{ on_end }
				, m_value{ NewSource() }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (m_current_frame.get()) {
					m_current_frame->Attribute(attribute, value);
				}
				else {
					switch (attribute)
					{
					case ColladaAttribute::id:
						m_value->SetId(value);
						break;
					case ColladaAttribute::name:
						m_value->SetName(value);
						break;
					default:
						throw Error::LoaderException{ String("Unexpected attribute {0}").arg(ParseAttribute(attribute)) };
					}
				}
			}

			void Text(const char* text, int len) override {
				if (m_current_frame) {
					m_current_frame->Text(text, len);
				}
			}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame) {
					m_current_frame->Begin(key);
				}
				else {
					switch (key)
					{
					case ColladaKeyword::technique_common:
						//	Just skip it
						break;
					case ColladaKeyword::accessor:
						m_current_frame.reset(new AccessorFrame{ [this](IAccessorPtr& value) {
							m_value->SetAccessor(value);
						} });
						break;
					case ColladaKeyword::float_array:
						m_current_frame.reset(new FloatArrayFrame{ [this](IFloatArrayPtr&value) {
							m_value->SetArray(value);
						} });
						break;
					default:
						throw Error::LoaderException{ String("Unexpected keyword {0}").arg(Parse(key)) };
					}
				}
			}

			bool End() override {
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
			std::function<void(ISourcePtr&)> m_on_end;
			ISourcePtr m_value;
			std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		};

		//
		//	ParamFrame
		//
		class InputFrame : public BaseFrame {
		public:
			InputFrame(std::function<void(IInputPtr&)> on_end)
				: m_value{ NewInput() }
				, m_on_end{ on_end }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				switch (attribute)
				{
				case ColladaAttribute::source:
					m_value->SetSourceRef(value);
					break;
				case ColladaAttribute::semantic:
					m_value->SetSemantic(ParseInputSemantic(value));
					break;
				default:
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				return true;
			}

		private:
			IInputPtr m_value;
			std::function<void(IInputPtr&)> m_on_end;
		};

	private:
		std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		IObjectPtr m_result{ nullptr };

		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};


	PUNK_REGISTER_CREATOR(CLSID_ColladaReader, (System::CreateInstance<ColladaReader, IReader>));
}
PUNK_ENGINE_END
