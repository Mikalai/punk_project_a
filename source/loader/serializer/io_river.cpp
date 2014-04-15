#include <attributes/water/river.h>
#include "io_static_geometry.h"
#include "io_string.h"
#include "io_vector.h"
#include "io_object.h"
#include "io_river.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveRiver(Core::Buffer *buffer, const Core::Object *o)
    {
        SaveObject(buffer, o);
        const Attributes::River* r = Cast<const Attributes::River*>(o);
        SaveString(buffer, r->GetStaticMeshFilename());
        SaveString(buffer, r->GetName());
        SaveVector3f(buffer, r->GetStreamPosition());
        SaveVector3f(buffer, r->GetFlowDirection());
        buffer->WriteReal32(r->GetFlowSpeed());
        SaveStaticGeometry(buffer, r->GetGeometry());
    }

    void LoadRiver(Core::Buffer *buffer, Core::Object *o)
    {
        LoadObject(buffer, o);
        Attributes::River* r = Cast<Attributes::River*>(o);
        Core::String filename;
        LoadString(buffer, filename);
        r->SetStaticMeshFilename(filename);

        Core::String name;
        LoadString(buffer, name);
        r->SetName(name);

        Math::vec3 position;
        LoadVector3f(buffer, position);
        r->SetStreamPosition(position);

        Math::vec3 dir;
        LoadVector3f(buffer, dir);
        r->SetFlowDirection(dir);

        r->SetFlowSpeed(buffer->ReadReal32());
        std::unique_ptr<Attributes::StaticGeometry> geom(new Attributes::StaticGeometry);
        LoadStaticGeometry(buffer, geom.get());
        r->SetGeometry(geom.release());
    }
}
PUNK_ENGINE_END
