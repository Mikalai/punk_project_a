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
        bool fullscreen {false};
        int bits_per_pixel {32};
        int refresh_frequency {60};
        int shadow_map_width {512};
        int shadow_map_height {512};
        bool use_multisampling {false};
        int multisampling_depth {2};
        bool use_coveragesampling {false};
        int coverage_depth {4};
        bool disable_3d_graphics {false};
    };
}
PUNK_ENGINE_END

#endif // CANVAS_DESCIPTION_H
