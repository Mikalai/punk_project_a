#ifndef VIDEO_DRIVER_CAPS_H
#define VIDEO_DRIVER_CAPS_H

namespace Gpu
{
    struct VideoDriverSettings
    {
        bool IsMultisamplingEnabled {false};
        bool IsCoverageSamplingEnabled {false};
        unsigned ShadowMapSize {512};
    };
}

#endif // VIDEO_DRIVER_CAPS_H
