#ifndef _H_ICOMPONENT_NORMAL
#define _H_ICOMPONENT_NORMAL

#include <config.h>
#include <cstdint>
#include <core/iobject.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IVertexNormalStream, "967C453B-EC0C-4E80-8091-8AA27EF417E7");

	class IVertexNormalStream : public Core::IObject {
	public:
		virtual const Math::vec3* GetVertexNormal(std::uint32_t index) const = 0;
		virtual void SetVertexNormal(std::uint32_t index, const Math::vec3& value) = 0;
		virtual void SetVertexNormals(const Math::vec3v& value) = 0;
		virtual bool HasVertexNormals() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_NORMAL