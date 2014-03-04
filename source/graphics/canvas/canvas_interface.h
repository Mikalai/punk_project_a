#ifndef PUNK_CANVAS_INTERFACE_H
#define PUNK_CANVAS_INTERFACE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class CanvasDescription;

    class ICanvas {
    public:
        virtual void SetFullscreen(bool value) = 0;
    };

    extern "C" PUNK_ENGINE_API ICanvas* CreateCanvas(const CanvasDescription& desc);
    extern "C" PUNK_ENGINE_API void DestroyCanvas(ICanvas* value);
}
PUNK_ENGINE_END

#endif // PUNK_CANVAS_INTERFACE_H
