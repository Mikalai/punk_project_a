#ifndef _H_PUNK_AI_NAVI_MESH
#define _H_PUNK_AI_NAVI_MESH

#include <config.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include "inavi_mesh.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace AI {

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

		void QueryInterface(const Core::Guid& type, void** object) override;

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
        Core::String m_name;
		Math::mat4 m_transfrom;
        Points m_points;
        Normals m_normals;
        Faces m_faces;

        PUNK_OBJECT_DEFAULT_IMPL(NaviMesh)
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_AI_NAVI_MESH
