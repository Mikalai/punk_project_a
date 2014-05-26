#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

#include <core/iobject.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "ianimation.h"
#include "animation_track.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

    class PUNK_ENGINE_LOCAL Animation : public IAnimation
	{		
	public:
		Animation();
        virtual ~Animation();

		void QueryInterface(const Core::Guid& type, void** object) override;

		void AddPositionKey(int frame, Math::vec3& position) override;
		void AddRotationKey(int frame, Math::quat& rotation) override;
		Math::vec3& GetOrCreatePositionKey(int frame) override;
		Math::quat& GetOrCreateRotationKey(int frame) override;
		const Math::vec3 GetPosition(float frame) const override;
		const Math::quat GetRotation(float frame) const override;
		void SetPositionTrack(const AnimationTrack<Math::vec3>& track) override { m_pos_track = track; }
		void SetRotationTrack(const AnimationTrack<Math::quat>& track) override { m_rot_track = track; }
		const AnimationTrack<Math::vec3>& GetPositionTrack() const override { return m_pos_track; }
		const AnimationTrack<Math::quat>& GetRotationTrack() const override { return m_rot_track; }
		const Core::String& GetName() const override;
		void SetName(const Core::String& value) override;

	private:
		AnimationTrack<Math::vec3> m_pos_track;
		AnimationTrack<Math::quat> m_rot_track;
		Core::String m_name;
        PUNK_OBJECT_DEFAULT_IMPL(Animation)
	};    
}
PUNK_ENGINE_END

#endif
