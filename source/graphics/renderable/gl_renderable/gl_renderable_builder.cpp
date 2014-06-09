#include <core/ifactory.h>
#include "gl_renderable_builder.h"
#include <graphics/primitives/gl_primitive/module.h>
#include <graphics/primitives/irenderable.h>
#include <graphics/primitives/module.h>
#include <graphics/video_driver/module.h>


PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL {

        GlRenderableBuilder::GlRenderableBuilder()
            : RenderableBuilder()
        {}

        GlRenderableBuilder::~GlRenderableBuilder() {
        }
		
		void GlRenderableBuilder::QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IRenderableBuilder });
		}

       /* template<typename VertexType>
        IRenderable* Cook(PrimitiveType type, const IVertexArray* buffer, IVideoDriver* driver) {
			IRenderable* result = Cook()
            if (type == GL_POINTS) {
                auto result = CreatePoints(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else if (type == GL_LINES) {
                auto result = CreateLines(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else if (type == GL_TRIANGLES) {
                auto result = CreateTriangles(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else
                throw Error::GraphicsException(L"Unsupported primitive type");
        }*/

        template<typename Vertex>
        void QuadsToTriangles(std::vector<Vertex>& inout, PrimitiveType src_type)
        {
            std::vector<Vertex> in = inout;
            if (src_type == PrimitiveType::QUADS)
            {
                if (in.size() % 4 != 0)
                    throw Error::OpenGLException(L"Invalid vertex buffer. Count of vertex is not devided by 4");

                inout.clear();

                for (size_t i = 0; i != in.size(); i += 4)
                {
                    const Vertex& v1 = in[i];
                    const Vertex& v2 = in[i+1];
                    const Vertex& v3 = in[i+2];
                    const Vertex& v4 = in[i+3];

                    inout.push_back(v1);
                    inout.push_back(v2);
                    inout.push_back(v3);

                    inout.push_back(v3);
                    inout.push_back(v4);
                    inout.push_back(v1);
                }
            }
        }

        template<typename Vertex>
        void PolygonToTriangles(std::vector<Vertex>& inout, PrimitiveType src_type)
        {
            std::vector<Vertex> in = inout;
            if (src_type == PrimitiveType::POLYGON)
            {
                if (in.size() < 3)
                    throw Error::OpenGLException(L"Invalid vertex buffer. Not enough points");
                inout.clear();

                for (size_t i = 1; i != in.size() - 1; ++i)
                {
                    inout.push_back(in[0]);
                    inout.push_back(in[i]);
                    inout.push_back(in[i+1]);
                }
            }
        }


        template<typename Vertex>
        void ModifyVertexInput(std::vector<Vertex>& inout, PrimitiveType src_type) {
            if (src_type == PrimitiveType::QUADS)
                QuadsToTriangles(inout, src_type);
            else if (src_type == PrimitiveType::POLYGON)
                PolygonToTriangles(inout, src_type);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferP(const std::vector<Math::vec4>& position)
        {
            typedef Vertex<VertexComponent::Position> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            for (auto& p : position)
            {
                VertexType v;
                v.m_position = p;
                vb.push_back(v);
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
            return ToRenderable(m_primitive_type, &array, nullptr);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color)
        {
            if (position.size() != color.size())
                throw Error::OpenGLException(L"Position and color buffer has different size");

            typedef Vertex<VertexComponent::Position, VertexComponent::Color> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            auto p_it = position.begin();
            auto c_it = color.begin();
            while (p_it != position.end() && c_it != color.end())
            {
                VertexType v;
                v.m_position = *p_it;
                v.m_color = *c_it;
                vb.push_back(v);

                ++p_it;
                ++c_it;
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
            return ToRenderable(m_primitive_type, &array, nullptr);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord)
        {
            if (position.size() != texcoord.size())
				throw Error::OpenGLException(L"Position and texture buffer has different size");

            typedef Vertex<VertexComponent::Position, VertexComponent::Texture0> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            auto p_it = position.begin();
            auto t_it = texcoord.begin();
            while (p_it != position.end() && t_it != texcoord.end())
            {
                VertexType v;
                v.m_position = *p_it;
                v.m_texture0 = *t_it;
                vb.push_back(v);

                ++p_it;
                ++t_it;
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
			return ToRenderable(m_primitive_type, &array, nullptr);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color)
        {
            if (position.size() != texcoord.size() || position.size() != color.size())
                throw Error::OpenGLException(L"Position, texture or color buffer has different size");

            typedef Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            auto p_it = position.begin();
            auto t_it = texcoord.begin();
            auto c_it = color.begin();
            while (p_it != position.end() && t_it != texcoord.end() && c_it != color.end())
            {
                VertexType v;
                v.m_position = *p_it;
                v.m_texture0 = *t_it;
                v.m_color = *c_it;
                vb.push_back(v);

                ++p_it;
                ++t_it;
                ++c_it;
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
			return ToRenderable(m_primitive_type, &array, nullptr);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal)
        {
            if (position.size() != normal.size())
				throw Error::OpenGLException(L"Position and normal buffer has different size");

            typedef Vertex<VertexComponent::Position, VertexComponent::Normal> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            auto p_it = position.begin();
            auto n_it = normal.begin();
            while (p_it != position.end() && n_it != normal.end())
            {
                VertexType v;
                v.m_position = *p_it;
                v.m_normal = *n_it;
                vb.push_back(v);

                ++p_it;
                ++n_it;
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
			return ToRenderable(m_primitive_type, &array, nullptr);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord)
        {
            if (position.size() != texcoord.size() || position.size() != normal.size())
				throw Error::OpenGLException(L"Position, texture or normal buffer has different size");

            typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> VertexType;
            std::vector<VertexType> vb;
            vb.reserve(position.size());
            auto p_it = position.begin();
            auto t_it = texcoord.begin();
            auto n_it = normal.begin();
            while (p_it != position.end() && t_it != texcoord.end() && n_it != normal.end())
            {
                VertexType v;
                v.m_position = *p_it;
                v.m_texture0 = *t_it;
                v.m_normal = *n_it;
                vb.push_back(v);

                ++p_it;
                ++t_it;
                ++n_it;
            }

            ModifyVertexInput(vb, m_high_level_type);
            VertexArray<VertexType> array{vb};
			return ToRenderable(m_primitive_type, &array, nullptr);
        }

        void GlRenderableBuilder::Begin(const PrimitiveType& value)
        {
            ValidateBegin();
            m_high_level_type = value;            
            m_primitive_type = HighLevelPrimitiveTypeToBasic(m_high_level_type);
            //m_current_frame = m_driver->BeginFrame();
        }

        void GlRenderableBuilder::End()
        {
            ValidateEnd();

            //m_current_frame->BeginRendering();
            //m_current_frame->LowLevelRender(renderable);
            //m_current_frame->EndRendering();
        }

        IRenderable* GlRenderableBuilder::ToRenderable()
        {
            int64_t c = 0;
            c |= m_vertex.empty() ? 0 : VertexComponent::Position::Value();
            c |= m_color.empty() ? 0 : VertexComponent::Color::Value();
            c |= m_normal.empty() ? 0 : VertexComponent::Normal::Value();
            c |= m_texcoord.empty() ? 0 : VertexComponent::Texture0::Value();

            IRenderable* renderable;
            if (c == Vertex<VertexComponent::Position>::Value())
                renderable = BuildVertexBufferP(m_vertex);
            else if (c == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
                renderable = BuildVertexBufferPC(m_vertex, m_color);
            else if (c == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
                renderable = BuildVertexBufferPT(m_vertex, m_texcoord);
            else if (c == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
                renderable = BuildVertexBufferPTC(m_vertex, m_texcoord, m_color);
            else if (c == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
                renderable = BuildVertexBufferPN(m_vertex, m_normal);
            else if (c == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
                renderable = BuildVertexBufferPNT0(m_vertex, m_normal, m_texcoord);
            else
				throw Error::OpenGLException(L"Unsupported vertex type in RenderableBuilder");
            return renderable;
        }

		template<PrimitiveType PT, typename IT, typename ... VC>
		struct CreateBatch {
			using Type = GlBatch < PT, IT, VC... > ;
		};		

		template<PrimitiveType PT, typename IT>
		IRenderable* CreateRenderable(std::uint64_t vertex_type) {
			if (vertex_type == Vertex<VertexComponent::Position>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Color>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Texture0>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Normal>::Type;
			else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
				return new CreateBatch<PT, IT, VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> ::Type;
			else
				throw Error::OpenGLException("Unsupported vertex type");
		}
		template<PrimitiveType PT>
		IRenderable* CreateRenderable(std::uint64_t vertex_type, std::uint64_t index_size) {
			if (index_size == sizeof(std::uint16_t)) {
				return CreateRenderable<PT, std::uint16_t>(vertex_type);
			}
			else if (index_size == sizeof(std::uint32_t)) {
				return CreateRenderable<PT, std::uint32_t>(vertex_type);
			}
			else if (index_size == 0) {
				return CreateRenderable<PT, std::nullptr_t>(vertex_type);
			}
			else
				throw Error::OpenGLException("Unsupported index size");			
		}

		IRenderable* CreateRenderable(PrimitiveType type, std::uint64_t vertex_type, std::uint64_t index_size){
			IRenderable* result = nullptr;
			switch (type)
			{
			case PrimitiveType::POINTS:
				result = CreateRenderable<PrimitiveType::POINTS>(vertex_type, index_size);
				break;
			case PrimitiveType::LINE_STRIP:
				result = CreateRenderable<PrimitiveType::LINE_STRIP>(vertex_type, index_size);
				break;
			case PrimitiveType::LINE_LOOP:
				result = CreateRenderable<PrimitiveType::LINE_LOOP>(vertex_type, index_size);
				break;
			case PrimitiveType::LINES:
				result = CreateRenderable<PrimitiveType::LINES>(vertex_type, index_size);
				break;
			case PrimitiveType::LINE_STRIP_ADJANCECY:
				result = CreateRenderable<PrimitiveType::LINE_STRIP_ADJANCECY>(vertex_type, index_size);
				break;
			case PrimitiveType::LINES_ADJANCENCY:
				result = CreateRenderable<PrimitiveType::LINES_ADJANCENCY>(vertex_type, index_size);
				break;
			case PrimitiveType::TRIANGLE_STRIP:
				result = CreateRenderable<PrimitiveType::TRIANGLE_STRIP>(vertex_type, index_size);
				break;
			case PrimitiveType::TRIANGLE_FAN:
				result = CreateRenderable<PrimitiveType::TRIANGLE_FAN>(vertex_type, index_size);
				break;
			case PrimitiveType::TRIANGLES:
				result = CreateRenderable<PrimitiveType::TRIANGLES>(vertex_type, index_size);
				break;
			case PrimitiveType::TRIANGLE_STRIP_ADJANCECY:
				result = CreateRenderable<PrimitiveType::TRIANGLE_STRIP_ADJANCECY>(vertex_type, index_size);
				break;
			case PrimitiveType::TRIANGLES_ADJANCECY:
				result = CreateRenderable<PrimitiveType::TRIANGLES_ADJANCECY>(vertex_type, index_size);
				break;
			case PrimitiveType::QUADS:
				result = CreateRenderable<PrimitiveType::QUADS>(vertex_type, index_size);
				break;
			case PrimitiveType::POLYGON:
				result = CreateRenderable<PrimitiveType::POLYGON>(vertex_type, index_size);
				break;
			default:
				throw Error::OpenGLException("Can't create renderable of specified primitive type");
			}
			return result;
		}

		IRenderable* GlRenderableBuilder::ToRenderable(PrimitiveType type, IVertexArray* vb, IIndexArray* ib) {
			IRenderable* result = CreateRenderable(type, vb->GetVertexType(), ib ? ib->GetIndexSize() : 0);
			result->Cook(vb, ib);
			return result;
		}


		PUNK_REGISTER_CREATOR(IID_IRenderableBuilder, Core::CreateInstance<GlRenderableBuilder>);
    }    	
}
PUNK_ENGINE_END
