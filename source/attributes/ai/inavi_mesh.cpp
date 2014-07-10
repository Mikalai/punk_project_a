#include <system/factory/module.h>
#include <memory.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include "inavi_mesh.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL NaviMesh : public INaviMesh
	{
	public:
		typedef std::vector<Math::vec3> Points;
		typedef std::vector<Math::vec3> Normals;
		typedef std::vector<Math::ivec3> Faces;
	public:
		NaviMesh();
		NaviMesh(const NaviMesh&) = delete;
		NaviMesh& operator = (const NaviMesh&) = delete;
		virtual ~NaviMesh();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	INaviMesh
		void SetTransform(const Math::mat4& value) override;
		const Math::mat4& GetTranform() const override;
		void SetVertexPositions(const Math::vec3* value, std::uint32_t count) override;
		void SetVertexNormals(const Math::vec3* value, std::uint32_t count) override;
		void SetTriangles(const Math::ivec3* value, std::uint32_t count) override;
		std::uint32_t GetVertexCount() const override;
		const Math::vec3& GetVertexPosition(std::uint32_t index) const override;
		const Math::vec3& GetVertexNormal(std::uint32_t index) const override;
		std::uint32_t GetTrianglesCount() const override;
		const Math::ivec3& GetTriangle(std::uint32_t index) const override;
		void SetName(const Core::String& value) override;
		const Core::String& GetName() const override;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		Math::mat4 m_transfrom;
		Points m_points;
		Normals m_normals;
		Faces m_faces;
	};

	void NaviMesh::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_INaviMesh });
	}

	std::uint32_t NaviMesh::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t NaviMesh::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

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

	PUNK_REGISTER_CREATOR(CLSID_NaviMesh, (System::CreateInstance<NaviMesh, INaviMesh>));
}
PUNK_ENGINE_END
