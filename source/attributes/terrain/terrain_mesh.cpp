#include <attributes/geometry/igeometry.h>
#include "terrain_mesh.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    TerrainMesh::TerrainMesh()
        : m_geometry(nullptr)
        , m_task(nullptr)
    {}

    TerrainMesh::~TerrainMesh()
    {
        delete m_task;
    }

    void TerrainMesh::SetGeometry(IGeometry* geom)
    {
        m_geometry = geom;
    }

    IGeometry* TerrainMesh::GetGeometry()
    {
        return m_geometry;
    }

    const IGeometry* TerrainMesh::GetGeometry() const
    {
        return m_geometry;
    }

    void TerrainMesh::SetStaticMeshFilename(const Core::String& filename)
    {
        m_filename = filename;
    }

    const Core::String TerrainMesh::GetStaticMeshFilename() const
    {
        return m_filename;
    }

    void TerrainMesh::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& TerrainMesh::GetName() const
    {
        return m_name;
    }

    Utility::AsyncParserTask* TerrainMesh::Task() const
    {
        return m_task;
    }

    Utility::AsyncParserTask* TerrainMesh::Task(Utility::AsyncParserTask* value)
    {
        if (m_task)
            delete m_task;
        return m_task = value;
    }
}
PUNK_ENGINE_END
