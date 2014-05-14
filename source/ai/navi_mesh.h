#ifndef _H_PUNK_AI_NAVI_MESH
#define _H_PUNK_AI_NAVI_MESH

#include <config.h>
#include <core/iobject.h>
#include <math/mat4.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace AI {

    class PUNK_ENGINE_API NaviMesh : public Core::IObject
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

        void SetTransform(const Math::mat4& value);
        const Math::mat4& GetTranform() const;

        static NaviMesh* CreateFromFile(const Core::String& path);

        const Math::vec3& GetPoint(int index) const;

        void SetPoints(const Points& value);
        void SetNormals(const Normals& value);
        void SetFaces(const Faces& value);

        const Points& GetPoints() const;
        const Faces& GetFaces() const;
        const Normals& GetNormals() const;

        void SetName(const Core::String& value);
        const Core::String& GetName() const;

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
