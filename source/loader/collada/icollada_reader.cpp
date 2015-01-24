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
#include <attributes/geometry/module.h>
#include <attributes/camera/module.h>
#include <attributes/light/module.h>

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
		input,
		vertices,
		vcount,
		p,
		polylist,
		mesh,
		geometry,
		library_geometries,
		perspective,
		xfov,
		yfov,
		aspect_ratio,
		znear,
		zfar,
		extra,
		optics,
		camera,
		library_cameras,
		point,
		color,
		constant_attenuation,
		linear_attenuation,
		quadratic_attenuation
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
		stride,
		set,
		material
	};

	std::pair<const char*, ColladaKeyword> collada_mapping[] {
		{ "float_array", ColladaKeyword::float_array },
		{ "param", ColladaKeyword::param },
		{ "accessor", ColladaKeyword::accessor },
		{ "technique_common", ColladaKeyword::technique_common },
		{ "source", ColladaKeyword::source },
		{ "input", ColladaKeyword::input },
		{ "vertices", ColladaKeyword::vertices },
		{ "vcount", ColladaKeyword::vcount },
		{ "p", ColladaKeyword::p },
		{ "polylist", ColladaKeyword::polylist },
		{ "mesh", ColladaKeyword::mesh },
		{ "geometry", ColladaKeyword::geometry },
		{ "library_geometries", ColladaKeyword::library_geometries },
		{ "perspective", ColladaKeyword::perspective },
		{ "xfov", ColladaKeyword::xfov },
		{ "yfov", ColladaKeyword::yfov },
		{ "aspect_ratio", ColladaKeyword::aspect_ratio },
		{ "znear", ColladaKeyword::znear },
		{ "zfar", ColladaKeyword::zfar },
		{ "extra", ColladaKeyword::extra },
		{ "optics", ColladaKeyword::optics },
		{ "camera", ColladaKeyword::camera },
		{ "library_cameras", ColladaKeyword::library_cameras  },
		{ "point", ColladaKeyword::point },
		{ "color", ColladaKeyword::color },
		{ "constant_attenuation", ColladaKeyword::constant_attenuation },
		{ "linear_attenuation", ColladaKeyword::linear_attenuation },
		{ "quadratic_attenuation", ColladaKeyword::quadratic_attenuation },
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
		{ "set", ColladaAttribute::set },
		{ "material", ColladaAttribute::material },		
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
		if (!strcmp(value, "VERTEX"))
			return InputSemantic::Vertex; 
		if (!strcmp(value, "NORMAL"))
			return InputSemantic::Normal;
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
					m_current_frame.reset(new InputFrame{ std::function < void(IInputSharedPtr&) > { [this](IInputSharedPtr& value) {
						m_result = value;
					} } });
					break;
				case ColladaKeyword::vertices:
					m_current_frame.reset(new VerticesFrame{ [this](IVerticesPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::vcount:
					m_current_frame.reset(new VertexCountListFrame{ [this](IVertexCountListPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::p:
					m_current_frame.reset(new PrimitivesListFrame{ [this](IPrimitivesListPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::polylist:
					m_current_frame.reset(new PolyListFrame{ [this](IPolyListPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::mesh:
					m_current_frame.reset(new MeshFrame{ [this](IMeshPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::geometry:
					m_current_frame.reset(new GeometryFrame{ [this](IGeometry2Ptr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::library_geometries:
					m_current_frame.reset(new LibraryGeometriesFrame{ [this](ILibraryGeometriesPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::perspective:
					m_current_frame.reset(new PerspectiveFrame{ [this](IPerspectivePtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::optics:
					m_current_frame.reset(new OpticsFrame{ [this](IOpticsPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::camera:
					m_current_frame.reset(new CameraFrame{ [this](ICamera2Ptr& value) {
						m_result = value;
					} });
					break;					
				case ColladaKeyword::library_cameras:
					m_current_frame.reset(new LibraryCamerasFrame{ [this](ILibraryCamerasPtr& value) {
						m_result = value;
					} });
					break;
				case ColladaKeyword::point:
					m_current_frame.reset(new PointFrame{ [this](IPointPtr& value) {
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
						++m_technique_common;
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
				else if (m_technique_common) {
					--m_technique_common;
					return false;
				}
				else {
					if (m_on_end) {
						m_on_end(m_value);
					}
					return true;
				}
			}

		private:
			int m_technique_common{ 0 };
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
				: m_value_shared{ NewInputShared() }
				, m_value{ m_value_shared }
				, m_on_end{ on_end }
			{}

			InputFrame(std::function<void(IInputSharedPtr&)> on_end)
				: m_value_shared{ NewInputShared() }
				, m_value{ m_value_shared }
				, m_on_end_shared{ on_end }
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
				case ColladaAttribute::offset:
					m_value_shared->SetOffset(Core::String(value).ToInt32());
					break;
				case ColladaAttribute::set:
					m_value_shared->SetSet(Core::String(value).ToInt32());
					break;
				default:
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				if (m_on_end_shared)
					m_on_end_shared(m_value_shared);
				return true;
			}

		private:
			IInputSharedPtr m_value_shared;
			IInputPtr m_value;			
			std::function<void(IInputPtr&)> m_on_end;
			std::function<void(IInputSharedPtr&)> m_on_end_shared;
		};

		//
		//	VerticesFrame
		//
		class VerticesFrame : public BaseFrame {
		public:
			VerticesFrame(std::function<void(IVerticesPtr&)> on_end)
				: m_value{ NewVertices() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::input:
						m_current_frame.reset(new InputFrame{ std::function < void(IInputPtr&) > {[this](IInputPtr& value) {
							m_value->AddInput(value);
						} } });
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
					case ColladaAttribute::name:
						m_value->SetName(value);
						break;
					case ColladaAttribute::id:
						m_value->SetId(value);
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
			IVerticesPtr m_value;
			std::function<void(IVerticesPtr&)> m_on_end;
		};

		//
		//	VertexCountListFrame
		//
		class VertexCountListFrame : public BaseFrame {
		public:

			VertexCountListFrame(std::function<void(IVertexCountListPtr&)> on_end)
				: m_value{ NewVertexCountList() }
				, m_on_end{ on_end }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
			}

			void Text(const char* text, int len) override {
				String s{ text, (std::uint32_t)len };
				auto values = s.Split(" ");
				for (int i = 0, max_i = values.Size(); i < max_i; ++i) {
					auto v = values[i].ToInt32();
					m_value->AddValue(v);
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				return true;
			}

		private:
			IVertexCountListPtr m_value;
			std::function<void(IVertexCountListPtr&)> m_on_end;
		};

		//
		//	VertexCountListFrame
		//
		class PrimitivesListFrame : public BaseFrame {
		public:

			PrimitivesListFrame(std::function<void(IPrimitivesListPtr&)> on_end)
				: m_value{ NewPrimitivesList() }
				, m_on_end{ on_end }
			{}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
			}

			void Text(const char* text, int len) override {
				String s{ text, (std::uint32_t)len };
				auto values = s.Split(" ");
				for (int i = 0, max_i = values.Size(); i < max_i; ++i) {
					auto v = values[i].ToInt32();
					m_value->AddValue(v);
				}
			}

			void Begin(ColladaKeyword key) override {}

			bool End() {
				if (m_on_end)
					m_on_end(m_value);
				return true;
			}

		private:
			IPrimitivesListPtr m_value;
			std::function<void(IPrimitivesListPtr&)> m_on_end;
		};

		//
		//	PolyListFrame
		//
		class PolyListFrame : public BaseFrame {
		public:
			PolyListFrame(std::function<void(IPolyListPtr&)> on_end)
				: m_value{ NewPolyList() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::input:
						m_current_frame.reset(new InputFrame{ std::function < void(IInputSharedPtr&) > {[this](IInputSharedPtr& value) {
							m_value->AddInput(value);
						} } });
						break;
					case ColladaKeyword::vcount:
						m_current_frame.reset(new VertexCountListFrame{ [this](IVertexCountListPtr& value) {
							m_value->SetVertexCountList(value);
						} });
						break;
					case ColladaKeyword::p:
						m_current_frame.reset(new PrimitivesListFrame{ [this](IPrimitivesListPtr& value) {
							m_value->SetPrimitivesList(value);
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
					case ColladaAttribute::count:
						m_value->SetSize(Core::String(value).ToInt32());
						break;
					case ColladaAttribute::material:
						m_value->SetMaterialRef(value);
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
			IPolyListPtr m_value;
			std::function<void(IPolyListPtr&)> m_on_end;
		};

		//
		//	MeshFrame
		//
		class MeshFrame : public BaseFrame {
		public:
			MeshFrame(std::function<void(IMeshPtr&)> on_end)
				: m_value{ NewMesh() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::source:
						m_current_frame.reset(new SourceFrame{ std::function < void(ISourcePtr&) > {[this](ISourcePtr& value) {
							m_value->AddSource(value);
						} } });
						break;
					case ColladaKeyword::vertices:
						m_current_frame.reset(new VerticesFrame{ [this](IVerticesPtr& value) {
							m_value->SetVertices(value);
						} });
						break;
					case ColladaKeyword::polylist:
						m_current_frame.reset(new PolyListFrame{ [this](IPolyListPtr& value) {
							m_value->AddPolylist(value);
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
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
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
			IMeshPtr m_value;
			std::function<void(IMeshPtr&)> m_on_end;
		};

		//
		//	GeoemtryFrame
		//
		class GeometryFrame : public BaseFrame {
		public:
			GeometryFrame(std::function<void(IGeometry2Ptr&)> on_end)
				: m_value{ NewGeometry2() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::mesh:
						m_current_frame.reset(new MeshFrame{ std::function < void(IMeshPtr&) > {[this](IMeshPtr& value) {
							Attributes::GeometryAccessor a{ m_value };
							a.SetMesh(value);
						} } });
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
					case ColladaAttribute::id:
						m_value->SetId(value);
						break;
					case ColladaAttribute::name:
						m_value->SetName(value);
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
			IGeometry2Ptr m_value;
			std::function<void(IGeometry2Ptr&)> m_on_end;
		};

		//
		//	LibraryGeometriesFrame
		//
		class LibraryGeometriesFrame : public BaseFrame {
		public:
			LibraryGeometriesFrame(std::function<void(ILibraryGeometriesPtr&)> on_end)
				: m_value{ NewLibraryGeometry() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::geometry:
						m_current_frame.reset(new GeometryFrame{ std::function < void(IGeometry2Ptr&) > {[this](IGeometry2Ptr& value) {
							m_value->AddGeometry(value);
						} } });
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
					case ColladaAttribute::id:
						m_value->SetId(value);
						break;
					case ColladaAttribute::name:
						m_value->SetName(value);
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
			ILibraryGeometriesPtr m_value;
			std::function<void(ILibraryGeometriesPtr&)> m_on_end;
		};

		//
		//	PerspectiveFrame
		//
		class PerspectiveFrame : public BaseFrame {
		public:
			PerspectiveFrame(std::function<void(IPerspectivePtr&)> on_end)
				: m_value{ NewPerspective() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				m_cur_word = key;				
			}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (attribute == ColladaAttribute::sid) {					
					m_float.SetSid(value);										
				} else 
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
			}

			void Text(const char* text, int len) override {
				if (m_cur_word != ColladaKeyword::bad) {
					m_float.SetValue(Core::String(text, len).ToFloat());

					switch (m_cur_word)
					{
					case ColladaKeyword::xfov:
						m_value->SetFovX(Math::degf::To<Math::tagRadian>(m_float));
						break;
					case ColladaKeyword::yfov:
						m_value->SetFovY(Math::degf::To<Math::tagRadian>(m_float));
						break;
					case ColladaKeyword::aspect_ratio:
						m_value->SetAspectRatio(m_float);
						break;
					case ColladaKeyword::zfar:
						m_value->SetZFar(m_float);
						break;
					case ColladaKeyword::znear:
						m_value->SetZNear(m_float);
						break;
					default:
						throw Error::LoaderException{ String{ "Can't parse keyword {0}" }.arg(Parse(m_cur_word)) };
					}
				}
			}

			bool End() {
				if (m_cur_word != ColladaKeyword::bad) {
					m_cur_word = ColladaKeyword::bad;
					return false;
				}
				else {
					if (m_on_end)
						m_on_end(m_value);
					return true;
				}
			}

		private:
			ColladaKeyword m_cur_word{ ColladaKeyword::bad };
			IPerspectivePtr m_value;
			Math::realf m_float;
			std::function<void(IPerspectivePtr&)> m_on_end;
		};

		//
		//	OpticsFrame
		//
		class OpticsFrame : public BaseFrame {
		public:
			OpticsFrame(std::function<void(IOpticsPtr&)> on_end)
				: m_value{ NewOptics() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {				
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::perspective:
						m_current_frame.reset(new PerspectiveFrame{ std::function < void(IPerspectivePtr&) > {[this](IPerspectivePtr& value) {
							m_value->SetProjection(To<IProjection>::From(value));
						} } });
						break;
					case ColladaKeyword::technique_common:
						m_technique_common++;
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
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
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
				else if (m_technique_common) {
					m_technique_common--;
					return false;
				}
				else {
					if (m_on_end)
						m_on_end(m_value);
					return true;
				}
			}

		private:
			int m_technique_common{ 0 };
			std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
			IOpticsPtr m_value;
			std::function<void(IOpticsPtr&)> m_on_end;
		};

		//
		//	CameraFrame
		//
		class CameraFrame : public BaseFrame {
		public:
			CameraFrame(std::function<void(ICamera2Ptr&)> on_end)
				: m_value{ NewCamera2() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_extra) {
					m_extra++;
					return;
				}

				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::optics:
						m_current_frame.reset(new OpticsFrame{ std::function < void(IOpticsPtr&) > {[this](IOpticsPtr& value) {
							m_value->SetOptics(value);
						} } });
						break;
					case ColladaKeyword::extra:
						m_extra++;
						break;
					default:
						throw Error::LoaderException{ String{ "Can't parse keyword {0}" }.arg(Parse(key)) };
					}
				}
			}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (m_extra)
					return;
				if (m_current_frame)
					m_current_frame->Attribute(attribute, value);
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
						throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
					}					
				}
			}

			void Text(const char* text, int len) override {
				if (m_current_frame)
					m_current_frame->Text(text, len);
			}

			bool End() {
				if (m_extra) {
					m_extra--;
					return false;
				}
				else if (m_current_frame) {
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
			int m_extra{ 0 };
			std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
			ICamera2Ptr m_value;
			std::function<void(ICamera2Ptr&)> m_on_end;
		};

		//
		//	LibraryGeometriesFrame
		//
		class LibraryCamerasFrame : public BaseFrame {
		public:
			LibraryCamerasFrame(std::function<void(ILibraryCamerasPtr&)> on_end)
				: m_value{ NewLibraryCameras() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				if (m_current_frame)
					m_current_frame->Begin(key);
				else {
					switch (key)
					{
					case ColladaKeyword::camera:
						m_current_frame.reset(new CameraFrame{ std::function < void(ICamera2Ptr&) > {[this](ICamera2Ptr& value) {
							m_value->AddCamera(value);
						} } });
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
					case ColladaAttribute::id:
						m_value->SetId(value);
						break;
					case ColladaAttribute::name:
						m_value->SetName(value);
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
			ILibraryCamerasPtr m_value;
			std::function<void(ILibraryCamerasPtr&)> m_on_end;
		};

		//
		//	PointFrame
		//
		class PointFrame : public BaseFrame {
		public:
			PointFrame(std::function<void(IPointPtr&)> on_end)
				: m_value{ NewPerspective() }
				, m_on_end{ on_end }
			{}

			void Begin(ColladaKeyword key) override {
				m_cur_word = key;
			}

			void Attribute(ColladaAttribute attribute, const char* value) override {
				if (attribute == ColladaAttribute::sid) {
					if (m_cur_word == ColladaKeyword::color)
						m_color.SetSid(value);
					else 
						m_float.SetSid(value);
				}
				else
					throw Error::LoaderException(String{ "Unexpected attribute {0}" }.arg(ParseAttribute(attribute)));
			}

			void Text(const char* text, int len) override {
				if (m_cur_word != ColladaKeyword::bad) {
					if (m_cur_word == ColladaKeyword::color) {
						Core::String s(text, len);
						auto items = s.Split(" ");
						for (int i = 0, max_i = items.Size(); i < max_i; ++i) {
							m_color.GetValue()[i] = items[i].ToFloat();
						}
					}
					else {
						m_float.SetValue(Core::String(text, len).ToFloat());
					}

					switch (m_cur_word)
					{
					case ColladaKeyword::color:
						m_value->SetColor(m_color);
						break;
					case ColladaKeyword::constant_attenuation:
						m_value->SetConstantAttenuation(m_float);
						break;
					case ColladaKeyword::linear_attenuation:
						m_value->SetLinearAttenuation(m_float);
						break;
					case ColladaKeyword::quadratic_attenuation:
						m_value->SetQuadraticsAttenuation(m_float);
						break;
					case ColladaKeyword::zfar:
						m_value->SetZFar(m_float);
						break;
					default:
						throw Error::LoaderException{ String{ "Can't parse keyword {0}" }.arg(Parse(m_cur_word)) };
					}
				}
			}

			bool End() {
				if (m_cur_word != ColladaKeyword::bad) {
					m_cur_word = ColladaKeyword::bad;
					return false;
				}
				else {
					if (m_on_end)
						m_on_end(m_value);
					return true;
				}
			}

		private:
			ColladaKeyword m_cur_word{ ColladaKeyword::bad };
			IPointPtr m_value;
			Math::realf m_float;
			Math::Color m_color;
			std::function<void(IPointPtr&)> m_on_end;
		};
	private:
		std::unique_ptr<BaseFrame> m_current_frame{ nullptr };
		IObjectPtr m_result{ nullptr };

		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};


	PUNK_REGISTER_CREATOR(CLSID_ColladaReader, (System::CreateInstance<ColladaReader, IReader>));
}
PUNK_ENGINE_END
