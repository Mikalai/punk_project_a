#ifndef RENDER_BUFFER_H
#define RENDER_BUFFER_H

#include "irender_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;

    class PUNK_ENGINE_API RenderBuffer : public IRenderBuffer
    {
    public:
        RenderBuffer(IVideoDriver* driver);
        RenderBuffer(const RenderBuffer&) = delete;
        RenderBuffer& operator = (const RenderBuffer&) = delete;
        virtual ~RenderBuffer();
        IVideoDriver* GetVideDriver();
        void Bind() override;
        void Unbind() override;

    private:
        IVideoDriver* m_driver;
    };
}
PUNK_ENGINE_END

#endif // RENDER_BUFFER_H
