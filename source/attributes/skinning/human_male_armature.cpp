#include "human_male_armature.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti HumanMaleArmatureType{ L"Attributes.HumanMaleArmature", typeid(HumanMaleArmature).hash_code(), { HumanArmature::Type() } };

	Core::Rtti* HumanMaleArmature::Type() {
		return &HumanMaleArmatureType;
	}

    HumanMaleArmature::HumanMaleArmature()
    {}

    HumanMaleArmature::~HumanMaleArmature()
    {}
}
PUNK_ENGINE_END
