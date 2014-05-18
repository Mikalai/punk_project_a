//#include <attributes/data/static_geometry.h>
//#include <attributes/terrain/terrain_mesh.h>
//#include "io_object.h"
//#include "io_string.h"
//#include "io_static_geometry.h"
//#include "io_terrain_mesh.h"
//
//PUNK_ENGINE_BEGIN
//namespace Loader {
//    void SaveTerrainMesh(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveObject(buffer, o);
//        const Attributes::TerrainMesh* m = Cast<const Attributes::TerrainMesh*>(o);
//        SaveString(buffer, m->GetName());
//        SaveString(buffer, m->GetStaticMeshFilename());
//        SaveStaticGeometry(buffer, m->GetGeometry());
//    }
//
//    void LoadTerrainMesh(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadObject(buffer, o);
//        Attributes::TerrainMesh* m = Cast<Attributes::TerrainMesh*>(o);
//        Core::String name;
//        LoadString(buffer, name);
//        m->SetName(name);
//
//        Core::String filename;
//        LoadString(buffer, filename);
//        m->SetStaticMeshFilename(filename);
//
//        Attributes::StaticGeometry* geometry = new Attributes::StaticGeometry();
//        LoadStaticGeometry(buffer, geometry);
//        m->SetGeometry(geometry);
//    }
//}
//PUNK_ENGINE_END
