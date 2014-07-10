#ifndef _H_INAVI_MESH
#define _H_INAVI_MESH

#include <config.h>
#include <cstdint>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class vec3;
	class ivec3;
	class mat4;
}
namespace Attributes {
	
	DECLARE_PUNK_GUID(IID_INaviMesh, "F8A31959-7761-4670-930C-D71850C4A6C2");
	DECLARE_PUNK_GUID(CLSID_NaviMesh, "30D5D0A8-D29C-4657-A731-757E46796030");

	class INaviMesh : public Core::IObject {
	public:
		virtual void SetTransform(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetTranform() const = 0;		
		virtual void SetVertexPositions(const Math::vec3* value, std::uint32_t count) = 0;
		virtual void SetVertexNormals(const Math::vec3* value, std::uint32_t count) = 0;
		virtual void SetTriangles(const Math::ivec3* value, std::uint32_t count) = 0;
		virtual std::uint32_t GetVertexCount() const = 0;
		virtual const Math::vec3& GetVertexPosition(std::uint32_t index) const = 0;
		virtual const Math::vec3& GetVertexNormal(std::uint32_t index) const = 0;
		virtual std::uint32_t GetTrianglesCount() const = 0;
		virtual const Math::ivec3& GetTriangle(std::uint32_t index) const = 0;				
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_INAVI_MESH