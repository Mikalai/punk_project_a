#ifndef _H_PUNK_AI_NAVI_TRIANGLE
#define _H_PUNK_AI_NAVI_TRIANGLE

#include <vector>
#include <config.h>
#include <string/string.h>


PUNK_ENGINE_BEGIN
namespace Core { class Object; }

namespace Attributes
{
	class NaviMesh;

	class PUNK_ENGINE_LOCAL NaviTriangle
	{		
	public:
		typedef std::vector<Core::Object*> ObjectsCollection;
	public:

		NaviTriangle(NaviMesh* mesh);	
		void AddObject(Core::Object* value);
		void RemoveObject(Core::Object* value);
		ObjectsCollection& GetObjects() { return m_collection; }

	private:			
		
		//	index of the triangle
		int m_index;
		//	points indeces of triangle
		int m_a, m_b, m_c;
		//	adjacent triangles
		int m_ab_triangle;
		int m_bc_triangle;
		int m_ca_triangle;
		NaviMesh* m_mesh;

		ObjectsCollection m_collection;
	};
}
PUNK_ENGINE_END


#endif	//	_H_PUNK_AI_NAVI_TRIANGLE
