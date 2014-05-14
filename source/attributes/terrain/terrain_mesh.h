#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Utility
{
    class AsyncParserTask;
}

namespace Attributes
{
    class IGeometry;
    class Material;

    class PUNK_ENGINE_API TerrainMesh : public Core::Object
    {
    public:
        TerrainMesh();
        TerrainMesh(const TerrainMesh&) = delete;
        TerrainMesh& operator = (const TerrainMesh&) = delete;
        virtual ~TerrainMesh();

        void SetGeometry(IGeometry* geom);
        IGeometry* GetGeometry();
        const IGeometry* GetGeometry() const;

        void SetStaticMeshFilename(const Core::String& filename);
        const Core::String GetStaticMeshFilename() const;

        void SetName(const Core::String& value);
        const Core::String& GetName() const;

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

    private:
        Core::String m_name;
        Core::String m_filename;
        IGeometry* m_geometry;
        Utility::AsyncParserTask* m_task;
        PUNK_OBJECT(TerrainMesh)
    };
}
PUNK_ENGINE_END


#endif // TERRAIN_MESH_H
