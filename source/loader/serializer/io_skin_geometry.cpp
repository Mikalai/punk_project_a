#include <attributes/data/skin_geometry.h>
#include "io_matrix.h"
#include "io_string.h"
#include "io_geometry.h"
#include "io_skin_geometry.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveSkinGeometry(Core::Buffer* buffer, const Core::Object* object)
    {
        SaveGeometry(buffer, object);
        const Attributes::SkinGeometry* s = Cast<const Attributes::SkinGeometry*>(object);
        SaveString(buffer, s->GetArmatureName());
        SaveString(buffer, s->GetName());
        SaveString(buffer, s->GetFilename());
        SaveMatrix4f(buffer, s->GetWorldOffset());
        //s->m_cpu_cache.Save(buffer);
    }

    void LoadSkinGeometry(Core::Buffer* buffer, Core::Object* object)
    {
        LoadGeometry(buffer, object);
        Attributes::SkinGeometry* s = Cast<Attributes::SkinGeometry*>(object);
        Core::String value;
        LoadString(buffer, value);
        s->SetArmatureName(value);

        LoadString(buffer, value);
        s->SetName(value);

        LoadString(buffer, value);
        s->SetFilename(value);

        Math::mat4 offset;
        LoadMatrix4f(buffer, offset);
        s->SetWorldOffset(offset);

        //s->m_cpu_cache.Load(buffer);
    }
}
PUNK_ENGINE_END
