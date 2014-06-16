//#ifndef _H_PUNK_OPENGL_TRIANGLE_FAN
//#define _H_PUNK_OPENGL_TRIANGLE_FAN
//
//#include "triangle_fans.h"
//
//#include <vector>
//#ifdef USE_OPENGL
//#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
//#else
//#endif
//
//#define CreateTriangleFansImplementation(VertexType) \
//    TriangleFan<VertexType>::TriangleFan(IVideoDriver* driver) \
//    : impl(new TriangleFanTemplate<VertexType>(driver)) {} \
//    TriangleFan<VertexType>::~TriangleFan() { \
//    delete impl; impl = nullptr; }\
//    void  TriangleFan<VertexType>::Cook(const IVertexArray* value) {\
//    dynamic_cast<TriangleFanTemplate<VertexType>*>(impl)->Cook(value); }\
//    void  TriangleFan<VertexType>::Bind(int64_t value) {\
//    impl->Bind(value); }\
//    void  TriangleFan<VertexType>::Unbind() { \
//    impl->Unbind(); }\
//    void  TriangleFan<VertexType>::LowLevelRender() {\
//    impl->LowLevelRender();}\
//    std::uint64_t TriangleFan<VertexType>::GetMemoryUsage() { \
//    return impl->GetMemoryUsage(); } \
//    bool TriangleFan<VertexType>::HasData() const { \
//    return impl->HasData(); }
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//#ifdef USE_OPENGL
//	template<typename VertexType>
//	using TriangleFanBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_FAN, VertexType>;
//#else
//#endif	//	USE_OPENGL
//
//	template<typename VertexType>
//    class PUNK_ENGINE_LOCAL TriangleFanTemplate: public TriangleFanBase<VertexType>
//	{
//		using Base = TriangleFanBase<VertexType>;
//	public:
//
//        TriangleFanTemplate(IVideoDriver* driver) : Base(driver) {}
//
//        void Cook(const IVertexArray* value)
//		{
//			Base::Clear();
//            std::vector<unsigned> ib(value->GetVertexCount());
//			for (unsigned i = 0; i < ib.size(); ++i)
//				ib[i] = i;
//			Base::SetVertexBuffer(value);
//			Base::SetIndexBuffer(ib);
//			Base::Cook();
//		}
//	};
//
//    namespace Constructor {
//        extern "C" PUNK_ENGINE_API ITriangleFan* CreateTriangleFan(std::int64_t vertex_type, class IVideoDriver* driver) {
//            if (vertex_type == Vertex<VertexComponent::Position>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Color>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Texture0>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Normal>>(driver);
//            else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
//                return new TriangleFan<Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>(driver);
//            else
//                throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
//        }
//    }
//
//#define VERTEX_1 Vertex<VertexComponent::Position>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
//    CreateTriangleFansImplementation(VERTEX_1)
//#undef VERTEX_1
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_OPENGL_TRIANGLE_FAN
