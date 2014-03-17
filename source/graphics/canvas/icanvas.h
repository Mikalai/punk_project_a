#ifndef PUNK_CANVAS_INTERFACE_H
#define PUNK_CANVAS_INTERFACE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System { class IWindow; }
namespace Graphics {
    class CanvasDescription;
    class IVideoDriver;

    class ICanvas {
    public:
        virtual void SetFullscreen(bool value) = 0;
        virtual System::IWindow* GetWindow() = 0;
        virtual const CanvasDescription& GetDescription() = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;
        virtual void SwapBuffers() = 0;
    };

    extern "C" PUNK_ENGINE_API ICanvas* CreateCanvas(const CanvasDescription& desc);
    extern "C" PUNK_ENGINE_API void DestroyCanvas(ICanvas* value);
}
PUNK_ENGINE_END

#endif // PUNK_CANVAS_INTERFACE_H
