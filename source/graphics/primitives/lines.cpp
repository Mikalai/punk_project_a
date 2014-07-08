//#include "lines.h"
//
//#include <vector>
//#ifdef USE_OPENGL
//#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
//#else
//#endif
//
//#define CreateLineImplementation(VertexType) \
//    Lines<VertexType>::Lines(IVideoDriver* driver) \
//    : impl(new LinesTemplate<VertexType>(driver)) {} \
//    Lines<VertexType>::~Lines() { \
//    delete impl; impl = nullptr; }\
//    void  Lines<VertexType>::Cook(const IVertexArray* value) {\
//    dynamic_cast<LinesTemplate<VertexType>*>(impl)->Cook(value); }\
//    void  Lines<VertexType>::Bind(std::int64_t value) {\
//    impl->Bind(value); }\
//    void  Lines<VertexType>::Unbind() { \
//    impl->Unbind(); }\
//    void  Lines<VertexType>::LowLevelRender() {\
//    impl->LowLevelRender();} \
//    std::uint64_t Lines<VertexType>::GetMemoryUsage() { \
//    return impl->GetMemoryUsage(); } \
//    bool Lines<VertexType>::HasData() const { \
//    return impl->HasData(); }
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//
//#ifdef USE_OPENGL
//    template<typename VertexType>
//    using LinesBase = OpenGL::VertexArrayObject2<PrimitiveType::LINES, VertexType>;
//#else
//#endif	//	USE_OPENGL
//
//
//    template<typename VertexType>
//    class PUNK_ENGINE_LOCAL LinesTemplate : public LinesBase<VertexType>
//    {
//        using Base = LinesBase<VertexType>;
//
//    public:
//
//        LinesTemplate(IVideoDriver* driver) : Base(driver) {}
//
//        void Cook(const IVertexArray* value)
//        {
//            Base::Clear();
//            std::vector<unsigned> ib(value->GetVertexCount());
//            for (unsigned i = 0; i < ib.size(); ++i)
//                ib[i] = i;
//            Base::SetVertexBuffer(value);
//            Base::SetIndexBuffer(ib);
//            Base::Cook();
//        }
//    };
//
//    extern PUNK_ENGINE_API ILinesPointer CreateLines(std::int64_t vertex_type, IVideoDriver* driver) {
//        if (vertex_type == Vertex<VertexComponent::Position>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Color>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Texture0>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Normal>>(driver), DestroyRenderable};
//        else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
//            return ILinesPointer{new Lines<Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>(driver), DestroyRenderable};
//        else
//            throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
//    }
//
//
//#define VERTEX_1 Vertex<VertexComponent::Position>
//    CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//        #define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
//            CreateLineImplementation(VERTEX_1)
//        #undef VERTEX_1
//
//}
//PUNK_ENGINE_END
