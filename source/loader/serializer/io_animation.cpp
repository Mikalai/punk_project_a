//#include <attributes/animation/animation.h>
//#include "io_string.h"
//#include "io_animation_track.h"
//#include "io_object.h"
//#include "io_animation.h"
//
//PUNK_ENGINE_BEGIN
//namespace Loader {
//    void SaveAnimation(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveObject(buffer, o);
//        const Attributes::Animation* animation = Cast<const Attributes::Animation*>(o);
//        SaveAnimationTrack(buffer, animation->GetPositionTrack());
//        SaveAnimationTrack(buffer, animation->GetRotationTrack());
//        SaveString(buffer, animation->GetName());
//    }
//
//    void LoadAnimation(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadObject(buffer, o);
//        Attributes::Animation* animation = Cast<Attributes::Animation*>(o);
//
//        Attributes::AnimationTrack<Math::vec3> position_track;
//        LoadAnimationTrack(buffer, position_track);
//        animation->SetPositionTrack(position_track);
//
//        Attributes::AnimationTrack<Math::quat> rotation_track;
//        LoadAnimationTrack(buffer, rotation_track);
//        animation->SetRotationTrack(rotation_track);
//
//        Core::String name;
//        LoadString(buffer, name);
//        animation->SetName(name);
//    }
//}
//PUNK_ENGINE_END
