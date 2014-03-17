#ifndef FRAME_BUFFER_TARGET_H
#define FRAME_BUFFER_TARGET_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class FrameBufferTarget {
        TargetNone,
        TargetFrontLeft,
        TargetFrontRight,
        TargetBackLeft,
        TargetBackRight,
        TargetFront,
        TargetBack,
        TargetLeft,
        TargetRight,
        TargetFrontBack
    };
}
PUNK_ENGINE_END

#endif // FRAME_BUFFER_TARGET_H
