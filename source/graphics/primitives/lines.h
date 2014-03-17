#ifndef _H_PUNK_LINES
#define _H_PUNK_LINES

#include "renderable.h"
#include "vertex.h"
#include "ilines.h"
#include "ivertex_array.h"

#define CreateLineInterface(VertexType)\
template<>\
class PUNK_ENGINE_LOCAL Lines<VertexType> : public Renderable, public ILines {\
public:\
    Lines<VertexType>(IVideoDriver* driver);\
    virtual ~Lines<VertexType>();\
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

    template<class VertexType> class Lines;

#define VERTEX_1 Vertex<VertexComponent::Position>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1

#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
    CreateLineInterface(VERTEX_1);
#undef VERTEX_1
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_LINES
