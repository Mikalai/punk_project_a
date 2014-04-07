#include <ostream>
#include <istream>
#include "object_animation_mixer.h"
#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{    
    Core::Rtti ObjectAnimationMixer::Type{L"Attributes.ObjectAnimationMixer",
                                          typeid(ObjectAnimationMixer).hash_code(),
                                         {&AnimationMixer::Type}};

	void ObjectAnimationMixer::AddTrack(const std::string& name, Animation* anim)
	{
        (void)name; (void)anim;
	}

	void ObjectAnimationMixer::RemoveTrack(const std::string& name)
	{
        (void)name;
	}

	Animation* ObjectAnimationMixer::GetOrCreateTrack(const Core::String& name)
	{
		auto it = m_tracks.find(name);
		if (it != m_tracks.end())
			return it->second.get();
		m_tracks[name].reset(new Animation);
		m_active[name] = false;
		m_factors[name] = 1;
		return m_tracks[name].get();
	}

    const Math::vec3 ObjectAnimationMixer::GetPosition(float frame)
	{
		Math::vec3 res;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				res += it->second->GetPosition(frame) * m_factors[it->first];
			}
		}
		return res;
	}

    const Math::quat ObjectAnimationMixer::GetRotation(float frame)
	{
		Math::quat res;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				res += it->second->GetRotation(frame) * m_factors[it->first];
			}
		}
		return res;
	}

	bool ObjectAnimationMixer::HasAnimation()
	{
		return !m_tracks.empty();
	}

	void ObjectAnimationMixer::DisableAllTracks()
	{
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			m_active[it->first] = false;
		}		
	}

	void ObjectAnimationMixer::EnableTrack(const Core::String name, bool flag)
	{
		m_active[name] = flag;
		NormalizeWeights();
	}

	//void ObjectAnimationMixer::SetLooping(const Core::String name, bool flag)
	//{
	//	m_tracks[name]->SetLooping(flag);		
	//}

	void ObjectAnimationMixer::SetTrackWeight(const Core::String name, float value)
	{
		m_factors[name] = value;
		NormalizeWeights();
	}

	void ObjectAnimationMixer::NormalizeWeights()
	{
		float total_weight= 0;
		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				total_weight += m_factors[it->first];
			}
		}

		for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
		{
			if (m_active[it->first])
			{
				m_factors[it->first] /= total_weight;
			}
		}
	}

}
PUNK_ENGINE_END
