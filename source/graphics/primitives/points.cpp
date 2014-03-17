#include <memory>
#include "points.h"

#include <vector>
#ifdef USE_OPENGL
#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
#else
#endif	//	USE_OPENGL

#define CreatePointImplementation(VertexType) \
    Points<VertexType>::Points(IVideoDriver* driver) \
    : impl(new PointsTemplate<VertexType>(driver)) {} \
    Points<VertexType>::~Points(){ \
    delete impl; impl = nullptr; }\
    void  Points<VertexType>::Cook(const IVertexArray* value) {\
    dynamic_cast<PointsTemplate<VertexType>*>(impl)->Cook(value); }\
    void  Points<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  Points<VertexType>::Unbind() { \
    impl->Unbind(); }\
    void  Points<VertexType>::Render() {\
    impl->Render();}\
    std::uint64_t Points<VertexType>::GetMemoryUsage() { \
    return impl->GetMemoryUsage(); } \
    bool Points<VertexType>::HasData() const { \
    return impl->HasData(); }

PUNK_ENGINE_BEGIN
namespace Graphics
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using PointsBase = OpenGL::VertexArrayObject2<PrimitiveType::POINTS, VertexType>;
#else
#endif

    template<typename VertexType>
    class PUNK_ENGINE_LOCAL PointsTemplate : public PointsBase<VertexType>
    {
        using Base = PointsBase<VertexType>;

    public:

        PointsTemplate(IVideoDriver* driver) : Base(driver) {}

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

    extern "C" PUNK_ENGINE_API IPointsUniquePtr CreatePoints(std::int64_t vertex_type, class IVideoDriver* driver) {
        if (vertex_type == Vertex<VertexComponent::Position>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Color>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Normal>>(driver), DestroyRenderable};
        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
            return IPointsUniquePtr{new Points<Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>(driver), DestroyRenderable};
        else
            throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
    }

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
            CreatePointImplementation(VERTEX_1)
        #undef VERTEX_1

}
PUNK_ENGINE_END
