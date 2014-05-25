//#ifndef ILINES_H
//#define ILINES_H
//
//#include <cstdint>
//#include <config.h>
//#include "irenderable.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//
//    class IVertexArray;
//    class IVideoDriver;
//
//    class PUNK_ENGINE_API ILines : public IRenderable {
//    public:
//        virtual void Cook(const IVertexArray* value) = 0;
//    };
//
//    using ILinesUniquePtr = std::unique_ptr<ILines, void (*)(IRenderable*)>;
//
//    extern PUNK_ENGINE_API ILinesUniquePtr CreateLines(std::int64_t vertex_type, class IVideoDriver* driver);
//}
//PUNK_ENGINE_END
//
//#endif // ILINES_H
