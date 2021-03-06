//#include <attributes/geometry/igeometry.h>
//#include "io_matrix.h"
//#include "io_string.h"
//#include "io_geometry.h"
//#include "io_static_geometry.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//
//    void SaveStaticGeometry(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveGeometry(buffer, o);
//        const Attributes::StaticGeometry* g = Cast<const Attributes::StaticGeometry*>(o);
//        SaveString(buffer, g->GetName());
//        SaveString(buffer, g->GetFilename());
//        SaveMatrix4f(buffer, g->GetWorldOffset());
//    }
//
//    void LoadStaticGeometry(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadGeometry(buffer, o);
//        Attributes::StaticGeometry* g = Cast<Attributes::StaticGeometry*>(o);
//        Core::String name;
//        LoadString(buffer, name);
//        g->SetName(name);
//
//        Core::String filename;
//        LoadString(buffer, filename);
//        g->SetFilename(filename);
//
//        Math::mat4 offset;
//        LoadMatrix4f(buffer, offset);
//        g->SetWorldOffset(offset);
//    }
//}
//PUNK_ENGINE_END
