#ifndef VIDEO_DRIVER_CAPS_H
#define VIDEO_DRIVER_CAPS_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    struct VideoDriverSettings
    {
        bool IsMultisamplingEnabled {false};
        bool IsCoverageSamplingEnabled {false};
        unsigned ShadowMapSize {512};
    };
}
PUNK_ENGINE_END

#endif // VIDEO_DRIVER_CAPS_H
