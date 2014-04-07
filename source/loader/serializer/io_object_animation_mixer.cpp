#include "io_object_animation_mixer.h"


//	bool ObjectAnimationMixer::Save(std::ostream& stream) const
//	{
//		int track_count = m_tracks.size();
//		stream.write(reinterpret_cast<const char*>(&track_count), sizeof(track_count));
//		for(auto it = m_tracks.begin(); it != m_tracks.end(); ++it)
//		{
//			const Core::String& name = it->first;
//			name.Save(stream);
//			it->second->Save(stream);

//			bool is_active = m_active.at(name);
//			float factor = m_factors.at(name);
//			stream.write(reinterpret_cast<const char*>(&is_active), sizeof(is_active));
//			stream.write(reinterpret_cast<const char*>(&factor), sizeof(factor));
//		}
//		return true;
//	}

//	bool ObjectAnimationMixer::Load(std::istream& stream)
//	{
//		int track_count= 0;
//		stream.read(reinterpret_cast<char*>(&track_count), sizeof(track_count));
//		for (int i = 0; i < track_count; ++i)
//		{
//			Core::String name;
//			name.Load(stream);
//			m_tracks[name].reset(new Animation);
//			m_tracks[name]->Load(stream);

//			bool is_active;
//			float factor;
//			stream.read(reinterpret_cast<char*>(&is_active), sizeof(is_active));
//			stream.read(reinterpret_cast<char*>(&factor), sizeof(factor));
//			m_active[name] = is_active;
//			m_factors[name] = factor;
//		}
//		return true;
//	}
