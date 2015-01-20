#ifndef _H_IGEOMETRY_ELEMENT
#define _H_IGEOMETRY_ELEMENT

#include <config.h>
#include <system/factory/interface.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IGeometryElement, "C85FD258-1479-4A38-B8F7-A43DED38352A");

	class IGeometryElement : public Core::IObject {
	public:
	};

	using IGeometryElementPtr = Core::Pointer < IGeometryElement > ;
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY_ELEMENT