#ifndef _H_ICOMPONENT_INDEX
#define _H_ICOMPONENT_INDEX

#include <config.h>
#include <cstdint>
#include <core/iobject.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IFaceIndexStream, "C7176CF8-9D56-4940-82DF-C0D7D6C48CEA");

	class IFaceIndexStream : public Core::IObject {
	public:
		virtual std::uint32_t GetTrianglesCount() const = 0;
		virtual const Math::ivec3* GetTriangle(std::uint32_t index) const = 0;
		virtual void SetTriangle(std::uint32_t index, const Math::ivec3& value) = 0;
		virtual void SetTriangles(const Math::ivec3v& value) = 0;
		virtual bool IsIndexed() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_INDEX
