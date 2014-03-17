#ifndef _H_PUNK_TRIANGLE_FAN
#define _H_PUNK_TRIANGLE_FAN

#include "itriangle_fans.h"
#include "renderable.h"
#include "vertex.h"

#define CreateTriangleFansInterface(VertexType)\
template<>\
class PUNK_ENGINE_LOCAL TriangleFan<VertexType> : public Renderable, public ITriangleFan {\
public:\
    TriangleFan<VertexType>(IVideoDriver* driver);\
    virtual ~TriangleFan<VertexType>();\
    void Cook(const IVertexArray* value);\
    virtual void Bind(int64_t) override;\
    virtual void Unbind() override;\
    virtual void Render() override;\
    virtual std::uint64_t GetMemoryUsage() override; \
    virtual bool HasData() const override; \
private:\
    Renderable* impl;\
}

PUNK_ENGINE_BEGIN
namespace Graphics {

    class VideoDriver;
    template<typename VertexType> class TriangleFan;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateTriangleFansInterface(VERTEX_1);
#undef VERTEX_1
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_TRIANGLE_FAN
