#ifndef _H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER
#define _H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER

#include <map>
#include <memory>
#include <config.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "animation_mixer.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class Animation;
    class PUNK_ENGINE_API ObjectAnimationMixer : public AnimationMixer
    {
        typedef std::map<Core::String, std::shared_ptr<Animation>> TrackType;
        typedef std::map<Core::String, bool> ActiveTracks;
        typedef std::map<Core::String, float> MixFactors;
        TrackType m_tracks;
        ActiveTracks m_active;
        MixFactors m_factors;
    public:
		ObjectAnimationMixer();
        void AddTrack(const std::string& name, Animation* anim);
        void RemoveTrack(const std::string& name);

        Animation* GetOrCreateTrack(const Core::String& name);

        const Math::vec3 GetPosition(float frame);
        const Math::quat GetRotation(float frame);

        bool HasAnimation();

        void DisableAllTracks();
        void EnableTrack(const Core::String name, bool flag);
        void SetLooping(const Core::String name, bool flag);
        void SetTrackWeight(const Core::String name, float value);

    private:
        void NormalizeWeights();

        PUNK_OBJECT_DEFAULT_IMPL(ObjectAnimationMixer)
    };
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_ANIMATION_OBJECT_ANIMATION_MixER
