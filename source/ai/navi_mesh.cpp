#include <core/ifactory.h>
#include <memory.h>
#include "navi_mesh.h"

PUNK_ENGINE_BEGIN
namespace AI
{
	DEFINE_PUNK_GUID(IID_INaviMesh, "F8A31959-7761-4670-930C-D71850C4A6C2");

    NaviMesh::NaviMesh()
	{}

    NaviMesh::~NaviMesh() {
    }

    void NaviMesh::SetTransform(const Math::mat4& value) {
        m_transfrom = value;
    }

    const Math::mat4& NaviMesh::GetTranform() const {
        return m_transfrom;
    }

    void NaviMesh::SetVertexPositions(const Math::vec3* value, std::uint32_t count) {
		m_points.resize(count);
		memcpy(m_points.data(), value, count*sizeof(Math::vec3));
    }

    void NaviMesh::SetVertexNormals(const Math::vec3* value, std::uint32_t count) {
		m_normals.resize(count);
		memcpy(m_normals.data(), value, count*sizeof(Math::vec3));
    }

    void NaviMesh::SetTriangles(const Math::ivec3* value, std::uint32_t count) {
		m_normals.resize(count);
		memcpy(m_faces.data(), value, count*sizeof(Math::ivec3));
    }

	std::uint32_t NaviMesh::GetVertexCount() const {
		return (std::uint32_t)m_points.size();
	}

    const Math::vec3& NaviMesh::GetVertexPosition(std::uint32_t index) const {
        return m_points[index];
    }

    const Math::vec3& NaviMesh::GetVertexNormal(std::uint32_t index) const {
		return m_normals[index];
    }

	std::uint32_t NaviMesh::GetTrianglesCount() const {
		return (std::uint32_t)m_faces.size();
	}

	const Math::ivec3& NaviMesh::GetTriangle(std::uint32_t index) const {
        return m_faces[index];
    }

    void NaviMesh::SetName(const Core::String& value) {
        m_name = value;
    }

    const Core::String& NaviMesh::GetName() const {
        return m_name;
    }    

	void NaviMesh::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == IID_INaviMesh) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	void CreateNaviMesh(void** object) {
		if (!object)
			return;
		*object = (void*)(new NaviMesh);
	}

	PUNK_REGISTER_CREATOR(IID_INaviMesh, CreateNaviMesh);
}
PUNK_ENGINE_END
