#ifndef PARSE_POSITION_TRACK_H
#define PARSE_POSITION_TRACK_H

#include <config.h>
#include <attributes/animation/animation_track.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Loader {
    extern bool ParsePositionTrack(Core::Buffer& buffer, Attributes::AnimationTrack<Math::vec3>& track);
}
PUNK_ENGINE_END

#endif // PARSE_POSITION_TRACK_H
