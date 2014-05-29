//#ifndef _H_PUNK_TRIANGLE_STRIPS
//#define _H_PUNK_TRIANGLE_STRIPS
//
//#include "itriangle_strip.h"
//#include "renderable.h"
//#include "vertex.h"
//
//#define CreateTriangleStripsInterface(VertexType)\
//template<>\
//class PUNK_ENGINE_LOCAL TriangleStrip<VertexType> : public Renderable, public ITriangleStrip {\
//public:\
//    TriangleStrip<VertexType>(IVideoDriver* driver);\
//    virtual ~TriangleStrip<VertexType>();\
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
//    template<typename VertexType> class TriangleStrip;
//
//    CreateTriangleStripsInterface(Vertex<VertexComponent::Position>);
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_TRIANGLE_STRIPS
