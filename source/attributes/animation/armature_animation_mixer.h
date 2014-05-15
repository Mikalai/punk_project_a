#ifndef _H_ARMATURE_ANIMATION
#define _H_ARMATURE_ANIMATION

#include <iosfwd>
#include <map>

#include <config.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <math/mat4.h>
#include <string/string.h>
#include "animation_mixer.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class IArmature;
    class Action;
	class BoneAnimation;
    class IBone;

    /**
     * @brief The ArmatureAnimationMixer class
     *  All bones should present in animations
     */
	class PUNK_ENGINE_API ArmatureAnimationMixer : public AnimationMixer
	{
	public:
        ArmatureAnimationMixer();
        ArmatureAnimationMixer(const ArmatureAnimationMixer&) = delete;
        ArmatureAnimationMixer& operator = (const ArmatureAnimationMixer&) = delete;
        virtual ~ArmatureAnimationMixer();

        virtual void SetTrackTime(float time) override;
        virtual float GetTrackTime() const override { return m_current_time; }
        virtual void SetLooping(size_t track, bool flag) override;

        //void UpdateBones(float frame);
        void SetArmature(IArmature* value);
		void DisableAllTracks();
		void EnableTrack(const Core::String&, bool flag);
		void SetTrackWeight(const Core::String&, float value);
		void SetLooping(const Core::String&, bool flag);
        //void AddBoneAnimation(const Core::String &track_name, const Core::String &bone_name, BoneAnimation *anim);
		bool GetBoneMatrix(const Core::String& bone, Math::mat4& matrix);		

        size_t GetTrackIndex(const Core::String& value);
        size_t GetBoneIndex(const Core::String& value);
        void EnableTrack(size_t track, bool flag);
        void SetTrackWeight(size_t track, float value);        
        bool GetBoneMatrix(size_t bone, Math::mat4& matrix);

        const Math::mat4& GetAnimatedGlobalMatrix(size_t bone) const;        

        IArmature* GetArmature();

    private:
		
        void UpdateGlobalMatrix();
        void UpdateBonesMatrix(IBone* value);

		/**	Contains info about track */
		struct PUNK_ENGINE_API TrackOption
		{
			float m_weight;
			bool m_enable;			
			bool m_loop;		

			TrackOption()
				: m_weight(1)
				, m_enable(false)
				, m_loop(true)
			{}
		};

		/** Interpolated data for each bone */
		struct PUNK_ENGINE_API InterpolatedData
		{
			Math::vec3 m_position;
			Math::quat m_rotation;
		};

        //std::map<Core::String, TrackOption> m_options;
		//	[ track_name: [ bone_name: animation ] ]
        //std::map<Core::String, std::map<Core::String, BoneAnimation*>> m_tracks;

        std::vector<TrackOption> m_options;
        std::vector<Core::String> m_tracks;
        std::vector<Action*> m_tracks_array;
        std::vector<std::vector<BoneAnimation*>> m_bones_animation_cache;

		//	result interpolated data for current time for each bone
		//	[bone_name: pos_rot]
        //	std::vector<InterpolatedData> m_result;
        std::vector<Math::mat4> m_animated_global_matrix;
        //std::map<Core::String, InterpolatedData> m_result;

		///	current time of the animation;
        float m_current_time;

        //  A place from which a structure can be get
        IArmature* m_armature;

        PUNK_OBJECT_DEFAULT_IMPL(ArmatureAnimationMixer)
	};
}
PUNK_ENGINE_END

#endif
