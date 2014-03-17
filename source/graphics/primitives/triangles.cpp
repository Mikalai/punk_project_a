#include <vector>

#ifdef USE_OPENGL
#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
#else
#endif

#include "triangles.h"

#define CreateTrianglesImplementation(VertexType) \
    Triangles<VertexType>::Triangles(IVideoDriver* driver) \
    : impl(new TrianglesTemplate<VertexType>(driver)) {} \
    Triangles<VertexType>::~Triangles<VertexType>() { \
    delete impl; impl = nullptr; }\
    void  Triangles<VertexType>::Cook(const IVertexArray* value) {\
    dynamic_cast<TrianglesTemplate<VertexType>*>(impl)->Cook(value); }\
    void  Triangles<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  Triangles<VertexType>::Unbind() { \
    impl->Unbind(); }\
    void  Triangles<VertexType>::Render() {\
    impl->Render();} \
    std::uint64_t Triangles<VertexType>::GetMemoryUsage() { \
    return impl->GetMemoryUsage(); } \
    bool Triangles<VertexType>::HasData() const { \
    return impl->HasData(); }

PUNK_ENGINE_BEGIN
namespace Graphics
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using TrianglesBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, VertexType>;
#else
#endif

    template<typename VertexType>
    class TrianglesTemplate: public TrianglesBase<VertexType>
    {
        using Base = TrianglesBase<VertexType>;

    public:

        TrianglesTemplate(IVideoDriver* driver) : Base(driver) {}

        void Cook(const IVertexArray* value)
        {
            Base::Clear();
            std::vector<unsigned> ib(value->GetVertexCount());
            for (unsigned i = 0; i < ib.size(); ++i)
                ib[i] = i;
            Base::SetVertexBuffer(value);
            Base::SetIndexBuffer(ib);
            Base::Cook();
        }
    };

    extern "C" PUNK_ENGINE_API ITrianglesUniquePtr CreateTriangles(std::int64_t vertex_type, class IVideoDriver* driver) {
        if (vertex_type == Vertex<VertexComponent::Position>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Color>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Normal>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
            return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else
            throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
    }

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTrianglesImplementation(VERTEX_1)
#undef VERTEX_1
}
PUNK_ENGINE_END
