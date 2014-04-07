#include "io_quaternion.h"
#include "io_vector.h"
#include "io_animation_track.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    using namespace Attributes;

    void LoadAnimationTrack(Core::Buffer *buffer, AnimationTrack<Math::quat> &value)
    {
        int frame_count = buffer->ReadSigned32();
        if (frame_count)
        {
            value.GetKeys().resize(frame_count);
            for (int i = 0; i != frame_count; ++i)
            {
                AnimationTrack<Math::quat>::Frame f = buffer->ReadSigned32();
                Math::quat v;
                LoadQuaternion(buffer, v);
                value.GetKeys()[i] = std::pair<AnimationTrack<Math::quat>::Frame, Math::quat>(f, v);
            }
        }
    }


    void LoadAnimationTrack(Core::Buffer* buffer, AnimationTrack<Math::vec3>& value)
    {
        int frame_count = buffer->ReadSigned32();
        if (frame_count)
        {
            value.GetKeys().resize(frame_count);
            for (int i = 0; i != frame_count; ++i)
            {
                AnimationTrack<Math::vec3>::Frame f = buffer->ReadSigned32();
                Math::vec3 v;
                LoadVector3f(buffer, v);
                value.GetKeys()[i] = std::pair<AnimationTrack<Math::vec3>::Frame, Math::vec3>(f, v);
            }
        }
    }

    void SaveAnimationTrack(Core::Buffer* buffer, const AnimationTrack<Math::quat>& value)
    {
        int frame_count = value.GetKeys().size();
        buffer->WriteSigned32(frame_count);
        if (frame_count)
        {
            for (auto& p : value.GetKeys())
            {
                buffer->WriteSigned32(p.first);
                SaveQuaternion(buffer, p.second);
            }
        }
    }

    void SaveAnimationTrack(Core::Buffer* buffer, const AnimationTrack<Math::vec3>& value)
    {
        int frame_count = value.GetKeys().size();
        buffer->WriteSigned32(frame_count);
        if (frame_count)
        {
            for (auto& p : value.GetKeys())
            {
                buffer->WriteSigned32(p.first);
                SaveVector3f(buffer, p.second);
            }
        }
    }
}
PUNK_ENGINE_END
