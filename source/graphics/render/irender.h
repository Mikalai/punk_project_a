#ifndef IRENDER_H
#define IRENDER_H

#include <config.h>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Math {
    class vec2;
    class mat4;
}

namespace Graphics {

    class Batch;
    class IFrameBuffer;
    class IVideoDriver;

    class IRender {
    public:
        virtual IVideoDriver* GetVideoDriver() = 0;
        virtual void AsyncBeginRendering(IFrameBuffer* buffer) = 0;
        virtual void WaitEndRendering() = 0;
        virtual void SubmitBatch(Batch* batch) = 0;
        virtual const Math::vec2 FindZRange(const Math::mat4& view) = 0;
    };

    using IRenderUniquePtr = std::unique_ptr<IRender, void (*)(IRender*)>;

    extern PUNK_ENGINE_API IRenderUniquePtr CreateRender(IVideoDriver* driver);
    extern PUNK_ENGINE_API void DestroyRender(IRender* value);
}
PUNK_ENGINE_END

#endif // IRENDER_H
