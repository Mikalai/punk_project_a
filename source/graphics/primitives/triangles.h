#ifndef _H_PUNK_TRIANGLES
#define _H_PUNK_TRIANGLES

#include "itriangles.h"
#include "renderable.h"
#include "vertex.h"

#define CreateTrianglesInterface(VertexType)\
template<>\
class PUNK_ENGINE_LOCAL Triangles<VertexType> : public Renderable, public ITriangles {\
public:\
    Triangles<VertexType>(IVideoDriver* driver);\
    virtual ~Triangles<VertexType>();\
    void Cook(const IVertexArray* value);\
    virtual void Bind(std::int64_t) override;\
    virtual void Unbind() override;\
    virtual void Render() override;\
    virtual std::uint64_t GetMemoryUsage() override; \
    virtual bool HasData() const override; \
private:\
    Renderable* impl;\
}

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;

    template<typename VertexType> class PUNK_ENGINE_LOCAL Triangles;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTrianglesInterface(VERTEX_1);
#undef VERTEX_1
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_TRIANGLES
