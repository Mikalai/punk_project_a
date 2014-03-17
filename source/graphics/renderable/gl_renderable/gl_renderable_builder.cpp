#include "gl_renderable_builder.h"
#include <graphics/primitives/gl_primitive/module.h>
#include <graphics/primitives/module.h>
#include <graphics/video_driver/module.h>


PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL {

        GlRenderableBuilder::GlRenderableBuilder(IVideoDriver* driver)
            : RenderableBuilder(driver)
        {}

        GlRenderableBuilder::~GlRenderableBuilder() {
        }


        template<typename VertexType>
        IRenderable* Cook(PrimitiveType type, const IVertexArray* buffer, IVideoDriver* driver) {
            if (type == PrimitiveType::POINTS) {
                auto result = CreatePoints(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else if (type == PrimitiveType::LINES) {
                auto result = CreateLines(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else if (type == PrimitiveType::TRIANGLES) {
                auto result = CreateTriangles(VertexType::Value(), driver);
                result->Cook(buffer);
                return result.release();
            }
            else
                throw Error::GraphicsException(L"Unsupported primitive type");
        }

        template<typename Vertex>
        void QuadsToTriangles(std::vector<Vertex>& inout, PrimitiveType src_type)
        {
            std::vector<Vertex> in = inout;
            if (src_type == PrimitiveType::QUADS)
            {
                if (in.size() % 4 != 0)
                    throw Error::GraphicsException(L"Invalid vertex buffer. Count of vertex is not devided by 4");

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
                    throw Error::GraphicsException(L"Invalid vertex buffer. Not enough points");
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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color)
        {
            if (position.size() != color.size())
                throw Error::GraphicsException(L"Position and color buffer has different size");

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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord)
        {
            if (position.size() != texcoord.size())
                throw Error::GraphicsException(L"Position and texture buffer has different size");

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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color)
        {
            if (position.size() != texcoord.size() || position.size() != color.size())
                throw Error::GraphicsException(L"Position, texture or color buffer has different size");

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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal)
        {
            if (position.size() != normal.size())
                throw Error::GraphicsException(L"Position and normal buffer has different size");

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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        IRenderable* GlRenderableBuilder::BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord)
        {
            if (position.size() != texcoord.size() || position.size() != normal.size())
                throw Error::GraphicsException(L"Position, texture or normal buffer has different size");

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
            return Cook<VertexType>(m_primitive_type, &array, m_driver);
        }

        void GlRenderableBuilder::Begin(const PrimitiveType& value)
        {
            ValidateBegin();
            m_high_level_type = value;
            m_primitive_type = value;
            //m_current_frame = m_driver->BeginFrame();
        }

        void GlRenderableBuilder::End()
        {
            ValidateEnd();

            //m_current_frame->BeginRendering();
            //m_current_frame->Render(renderable);
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
                throw Error::GraphicsException(L"Unsupported vertex type in RenderableBuilder");
            return renderable;
        }
    }
}
PUNK_ENGINE_END
