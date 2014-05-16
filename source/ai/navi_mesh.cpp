#include "navi_mesh.h"

PUNK_ENGINE_BEGIN
namespace AI
{
    NaviMesh::NaviMesh()
		: m_container{ this, Core::GetRootObject() }
    {
    }

    NaviMesh::~NaviMesh()
    {
    }

    void NaviMesh::SetTransform(const Math::mat4& value)
    {
        m_transfrom = value;
    }

    const Math::mat4& NaviMesh::GetTranform() const
    {
        return m_transfrom;
    }

    NaviMesh* NaviMesh::CreateFromFile(const Core::String& path)
    {
        return nullptr;
    }

    const Math::vec3& NaviMesh::GetPoint(int index) const
    {
        return m_points[index];
    }

    void NaviMesh::SetPoints(const Points &value)
    {
        m_points = value;
    }

    void NaviMesh::SetNormals(const Normals& value)
    {
        m_normals = value;
    }

    void NaviMesh::SetFaces(const Faces& value)
    {
        m_faces = value;
    }

    const NaviMesh::Points& NaviMesh::GetPoints() const
    {
        return m_points;
    }

    const NaviMesh::Normals& NaviMesh::GetNormals() const {
        return m_normals;
    }

    const NaviMesh::Faces& NaviMesh::GetFaces() const
    {
        return m_faces;
    }

    void NaviMesh::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& NaviMesh::GetName() const
    {
        return m_name;
    }    
}
PUNK_ENGINE_END
