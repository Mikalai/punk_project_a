#include <core/factory.h>
#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{	
	Animation::Animation()
	{        
	}

    Animation::~Animation() {}

	void Animation::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == IID_IAnimation ||
			type == Core::IID_IObject) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	void Animation::AddPositionKey(int frame, Math::vec3& position)
	{
		m_pos_track.AddKey(frame, position);
	}

	void Animation::AddRotationKey(int frame, Math::quat& rotation)
	{
		m_rot_track.AddKey(frame, rotation);
	}

	Math::vec3& Animation::GetOrCreatePositionKey(int time)
	{
		if (!m_pos_track.HasKeyAt(time))
			m_pos_track.AddKey(time, Math::vec3());
		bool flag;
		return m_pos_track.GetOriginalKey(time, flag);
	}

	Math::quat& Animation::GetOrCreateRotationKey(int time)
	{
		if (!m_rot_track.HasKeyAt(time))
			m_rot_track.AddKey(time, Math::quat());
		bool flag;
		return m_rot_track.GetOriginalKey(time, flag);
	}

	const Math::vec3 Animation::GetPosition(float time) const
	{
		return m_pos_track.GetKey(time);
	}

	const Math::quat Animation::GetRotation(float time) const
	{
		return m_rot_track.GetKey(time);
    }

    const Core::String& Animation::GetName() const
    {
        return m_name;
    }

    void Animation::SetName(const Core::String& value)
    {
        m_name = value;
    }    

	void CreateAnimation(void** object) {
		if (!object)
			return;
		*object = (void*)(new Animation);
	}

	PUNK_REGISTER_CREATOR(IID_IAnimation, CreateAnimation);
}
PUNK_ENGINE_END
