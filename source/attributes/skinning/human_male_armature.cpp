#include "human_male_armature.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti HumanMaleArmature::Type{L"Attributes.HumanMaleArmature",
                                       typeid(HumanMaleArmature).hash_code(),
        {&HumanArmature::Type}};

    HumanMaleArmature::HumanMaleArmature()
    {}

    HumanMaleArmature::~HumanMaleArmature()
    {}
}
PUNK_ENGINE_END
