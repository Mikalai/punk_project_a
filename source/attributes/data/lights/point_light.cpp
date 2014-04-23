#include <fstream>
#include <memory>
#include <string/module.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "point_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	Core::Rtti PointLightType{ "Attributes.PointLight", typeid(PointLight).hash_code(), { Light::Type() } };

	Core::Rtti* PointLight::Type() {
		return &PointLightType;
	}

	PointLight::PointLight()
	{
	}

//	PointLight::PointLight(const Utility::LightDesc& value)
//		: m_position(Math::vec3())
//		, m_color(value.m_color)
//		, m_distance(value.m_distance)
//		, m_energy(value.m_energy)
//		, m_linear_attenuation(value.m_linear_attenuation)
//		, m_quadratic_attenuation(value.m_quadratic_attenuation)
//	{
//	}

    PointLight::~PointLight()
    {
    }

	const Math::vec3 PointLight::GetPosition() const
	{
		return m_position;
	}

	void PointLight::SetPosition(const Math::vec3& value)
	{
		m_position = value;
	}    
}
PUNK_ENGINE_END

