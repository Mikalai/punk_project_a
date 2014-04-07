#include <attributes/data/static_geometry.h>
#include "terrain_mesh.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti TerrainMesh::Type{"Attributes.TerrainMesh",
                                 typeid(TerrainMesh).hash_code(),
        {&Core::Object::Type}};


    TerrainMesh::TerrainMesh()
        : m_geometry(nullptr)
        , m_task(nullptr)
    {}

    TerrainMesh::~TerrainMesh()
    {
        delete m_task;
    }

    void TerrainMesh::SetGeometry(StaticGeometry* geom)
    {
        m_geometry = geom;
    }

    StaticGeometry* TerrainMesh::GetGeometry()
    {
        return m_geometry;
    }

    const StaticGeometry* TerrainMesh::GetGeometry() const
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
