#ifndef _H_IGEOMETRY
#define _H_IGEOMETRY

#include <config.h>
#include <memory>
#include <cstdint>
#include <vector>
#include <core/iobject.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>


PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}

namespace Attributes {

	DECLARE_PUNK_GUID(IID_IGeometry, "3B04856F-622F-4AAD-984D-0A0FA5C34B27");

	class IGeometry 
		: public Core::IObject
	{
	public:
		virtual bool IsIndexed() const = 0;
		virtual bool Validate() = 0;
		virtual std::uint32_t GetVertexCount() = 0;		
		virtual void SetName(const Core::String& name) = 0;
		virtual const Core::String& GetName() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY