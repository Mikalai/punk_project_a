#ifndef _H_PUNK_UTILITY_SOUND
#define _H_PUNK_UTILITY_SOUND

#include <config.h>
#include <math/vec3.h>
#include <string/module.h>
#include <core/decl_property.h>

#include <iosfwd>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_API Sound
	{
	public:
        PROPERTY(Core::String, Name, m_name)
        PROPERTY(Core::String, Filename, m_filename)
        PROPERTY(float, Volume, m_volume)
        PROPERTY(float, Pitch, m_pitch)
        PROPERTY(float, MaxDistance, m_max_distance)
        PROPERTY(float, ReferenceDistance, m_reference_distance)
        PROPERTY(float, ConeAngleInner, m_cone_angle_inner)
        PROPERTY(float, ConeAngleOuter, m_cone_angle_outer)
        PROPERTY(float, ConeVolumeOuter, m_cone_volume_outer)
        PROPERTY(float, Attenuation, m_attenuation)

	private:
		Core::String m_name;
		Core::String m_filename;
		float m_volume;
		float m_pitch;
		float m_max_distance;
		float m_reference_distance;
		float m_cone_angle_inner;
		float m_cone_angle_outer;
		float m_cone_volume_outer;
		float m_attenuation;
	};
}
PUNK_ENGINE_END

#endif
