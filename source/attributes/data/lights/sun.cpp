#include <string/module.h>
#include "sun.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti SunType{ "Attributes.Sun", typeid(Sun).hash_code(), { Core::IObject::Type() } };

	Core::Rtti* Sun::Type() {
		return &SunType;
	}

    Sun::Sun()
    {
    }

    Sun::~Sun()
    {
    }

    void Sun::SetEnergy(float value)
    {
        m_energy = value;
    }

    float Sun::GetEnergy() const
    {
        return m_energy;
    }

    void Sun::SetColor(const Math::vec3& value)
    {
        m_color = value;
    }

    const Math::vec3& Sun::GetColor() const
    {
        return m_color;
    }

    void Sun::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& Sun::GetName() const
    {
        return m_name;
    }    
}
PUNK_ENGINE_END
