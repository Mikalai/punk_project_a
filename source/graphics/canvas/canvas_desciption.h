#ifndef CANVAS_DESCIPTION_H
#define CANVAS_DESCIPTION_H

#include <config.h>
#include <system/window/window_description.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class PUNK_ENGINE_API CanvasDescription : public System::WindowDescription
    {
    public:
        CanvasDescription();
        bool fullscreen = false;
        int bits_per_pixel = 32;

    };
}
PUNK_ENGINE_END

#endif // CANVAS_DESCIPTION_H
