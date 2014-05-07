#ifndef _H_IGEOMETRY_COOKER
#define _H_IGEOMETRY_COOKER

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}
namespace Attributes {
	
	class IGeometry;

	class IGeometryCooker {
	public:
		virtual void Cook(IGeometry* geometry, Graphics::IVertexArray* va, Graphics::IIndexArray* ia) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY_COOKER