//#ifndef _H_PUNK_OPENGL_POINTS_VAO
//#define _H_PUNK_OPENGL_POINTS_VAO
//
//#include "renderable.h"
//#include "vertex.h"
//#include "ipoints.h"
//
//#define CreatePointInterface(VertexType) \
//template<>\
//class PUNK_ENGINE_LOCAL Points<VertexType> : public Renderable, public IPoints {\
//public:\
//    Points<VertexType>(IVideoDriver* driver);\
//    virtual ~Points<VertexType>();\
//    void Cook(const IVertexArray* value);\
//    virtual void Bind(std::int64_t) override;\
//    virtual void Unbind() override;\
//    virtual void LowLevelRender() override;\
//    virtual std::uint64_t GetMemoryUsage() override; \
//    virtual bool HasData() const override; \
//private:\
//    Renderable* impl;\
//}
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//    class IVideoDriver;
//
//    template<typename VertexType> class Points;
//
//#define VERTEX_1 Vertex<VertexComponent::Position>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
//    CreatePointInterface(VERTEX_1);
//#undef VERTEX_1
//
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_OPENGL_POINTS_VAO
