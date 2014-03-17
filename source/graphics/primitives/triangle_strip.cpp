#ifndef _H_PUNK_OPENGL_TRIANGLE_STRIP
#define _H_PUNK_OPENGL_TRIANGLE_STRIP

#include <vector>
#include "triangle_strip.h"
#ifdef USE_OPENGL
#include <graphics/primitives/gl_primitive/gl_vertex_array_object.h>
#else
#endif

#define CreateTriangleStripsImplementation(VertexType) \
    TriangleStrip<VertexType>::TriangleStrip(IVideoDriver* driver) \
    : impl(new TriangleStripTemplate<VertexType>(driver)) {} \
    TriangleStrip<VertexType>::~TriangleStrip<VertexType>() { \
    delete impl; impl = nullptr; }\
    void  TriangleStrip<VertexType>::Cook(const IVertexArray* value) {\
    dynamic_cast<TriangleStripTemplate<VertexType>*>(impl)->Cook(value); }\
    void  TriangleStrip<VertexType>::Bind(int64_t value) {\
    impl->Bind(value); }\
    void  TriangleStrip<VertexType>::Unbind() { \
    impl->Unbind(); }\
    void  TriangleStrip<VertexType>::Render() {\
    impl->Render();}\
    std::uint64_t TriangleStrip<VertexType>::GetMemoryUsage() { \
    return impl->GetMemoryUsage(); } \
    bool TriangleStrip<VertexType>::HasData() const { \
    return impl->HasData(); }

PUNK_ENGINE_BEGIN
namespace Graphics
{
#ifdef USE_OPENGL
    template<typename VertexType>
    using TriangleStripBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLE_STRIP, VertexType>;
#else
#endif

    template<typename VertexType>
    class PUNK_ENGINE_LOCAL TriangleStripTemplate: public TriangleStripBase<VertexType>
    {
        using Base = TriangleStripBase<VertexType>;

    public:

        TriangleStripTemplate(IVideoDriver* driver) : Base(driver) {}

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

    namespace Constructor {
        extern "C" PUNK_ENGINE_API ITriangleStrip* CreateTriangleStrip(std::int64_t vertex_type, class IVideoDriver* driver) {
            if (vertex_type == Vertex<VertexComponent::Position>::Value())
                return new TriangleStrip<Vertex<VertexComponent::Position>>(driver);
            throw Error::GraphicsException(L"Can't create lines using " + Core::String::Convert(vertex_type) + L" vertex type");
        }
    }
    CreateTriangleStripsImplementation(Vertex<VertexComponent::Position>)
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_TRIANGLE_STRIP
