#include <attributes/skinning/human_armature.h>
#include "io_human_armature.h"
#include "io_armature.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveHumanArmature(Core::Buffer *buffer, const Core::Object *o)
    {
        SaveArmature(buffer, o);
    }

    void LoadHumanArmature(Core::Buffer *buffer, Core::Object *o)
    {
        LoadArmature(buffer, o);
        Attributes::HumanArmature* a = Cast<Attributes::HumanArmature*>(o);
        a->UpdateHierarchy();
    }

    void SaveHumanMaleArmature(Core::Buffer *buffer, const Core::Object *o)
    {
        SaveHumanArmature(buffer, o);
    }

    void LoadHumanMaleArmature(Core::Buffer *buffer, Core::Object *o)
    {
        LoadHumanArmature(buffer, o);
    }
}
PUNK_ENGINE_END
