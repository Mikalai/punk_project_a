#include <attributes/data/lights/sun.h>
#include "io_string.h"
#include "io_vector.h"
#include "io_object.h"
#include "io_sun.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    void SaveSun(Core::Buffer *buffer, const Core::Object *o)
    {
        SaveObject(buffer, o);
        const Attributes::Sun* s = Cast<const Attributes::Sun*>(o);
        buffer->WriteReal32(s->GetEnergy());
        SaveVector3f(buffer, s->GetColor());
        SaveString(buffer, s->GetName());
    }

    void LoadSun(Core::Buffer *buffer, Core::Object *o)
    {
        LoadObject(buffer, o);
        Attributes::Sun* s = Cast<Attributes::Sun*>(o);
        s->SetEnergy(buffer->ReadReal32());

        Math::vec3 color;
        LoadVector3f(buffer, color);
        s->SetColor(color);

        Core::String name;
        LoadString(buffer, name);
        s->SetName(name);
    }
}
PUNK_ENGINE_END
