//#include <vector>
//
//#ifdef USE_OPENGL
//#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
//#else
//#endif
//
//#include "triangles.h"
//
//#define CreateTrianglesImplementation(VertexType, IndexType) \
//    Triangles<VertexType, IndexType>::Triangles(IVideoDriver* driver) \
//    : impl(new TrianglesTemplate<VertexType, IndexType>(driver)) {} \
//    Triangles<VertexType, IndexType>::~Triangles<VertexType, IndexType>() { \
//    delete impl; impl = nullptr; }\
//    void  Triangles<VertexType, IndexType>::Cook(const IVertexArray* value) {\
//    dynamic_cast<TrianglesTemplate<VertexType, IndexType>*>(impl)->Cook(value); }\
//    void  Triangles<VertexType, IndexType>::Cook(const IVertexArray* vb, const IIndexArray* ib) {\
//    dynamic_cast<TrianglesTemplate<VertexType, IndexType>*>(impl)->Cook(vb, ib); }\
//    void  Triangles<VertexType, IndexType>::Bind(int64_t value) {\
//    impl->Bind(value); }\
//    void  Triangles<VertexType, IndexType>::Unbind() { \
//    impl->Unbind(); }\
//    void  Triangles<VertexType, IndexType>::LowLevelRender() {\
//    impl->LowLevelRender();} \
//    std::uint64_t Triangles<VertexType, IndexType>::GetMemoryUsage() { \
//    return impl->GetMemoryUsage(); } \
//    bool Triangles<VertexType, IndexType>::HasData() const { \
//    return impl->HasData(); }
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//#ifdef USE_OPENGL
//    template<typename VertexType, typename IndexType>
//    using TrianglesBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES, VertexType, IndexType>;
//#else
//#endif
//
//    template<typename VertexType, typename IndexType>
//    class TrianglesTemplate: public TrianglesBase<VertexType, IndexType>
//    {
//        using Base = TrianglesBase<VertexType, IndexType>;
//
//    public:
//
//        TrianglesTemplate(IVideoDriver* driver) : Base(driver) {}
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
//
//        void Cook(const IVertexArray *vb, const IIndexArray* ib) {
//            Base::Clear();
//            Base::SetVertexBuffer(vb);
//            Base::SetIndexBuffer(ib);
//            Base::Cook();
//        }
//    };
//
//    //extern PUNK_ENGINE_API ITrianglesUniquePtr CreateTriangles(std::int64_t vertex_type, IVideoDriver* driver) {
//    //    if (vertex_type == Vertex<VertexComponent::Position>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Color>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Texture0>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Texture0>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Normal>, unsigned>(driver), DestroyRenderable};
//    //    else if (vertex_type == Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>::Value())
//    //        return ITrianglesUniquePtr{new Triangles<Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>, unsigned>(driver), DestroyRenderable};
//    //    else
//    //        throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
//    //}
//
//#define VERTEX_1 Vertex<VertexComponent::Position>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0, VertexComponent::Flag, VertexComponent::Color>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Texture0>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Color, VertexComponent::Texture0>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//
//#define VERTEX_1 Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>
//    CreateTrianglesImplementation(VERTEX_1, unsigned)
//#undef VERTEX_1
//}
//PUNK_ENGINE_END
