//#ifndef ITRIANGLES_H
//#define ITRIANGLES_H
//
//#include <cstdint>
//#include <config.h>
//#include "irenderable.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//
//    class IVertexArray;
//    class IIndexArray;
//    class IVideoDriver;
//
//    class PUNK_ENGINE_API ITriangles : public IRenderable {
//    public:
//        virtual void Cook(const IVertexArray* value) = 0;
//        virtual void Cook(const IVertexArray *vb, const IIndexArray* ib) = 0;
//    };
//
//    using ITrianglesUniquePtr = std::unique_ptr<ITriangles, void (*)(IRenderable*)>;
//
//    extern PUNK_ENGINE_API ITrianglesUniquePtr CreateTriangles(std::int64_t vertex_type, class IVideoDriver* driver);
//}
//PUNK_ENGINE_END
//
//#endif // ITRIANGLES_H
