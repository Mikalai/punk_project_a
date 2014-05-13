#ifndef _H_GEOMETRY_COOKER
#define _H_GEOMETRY_COOKER

#include <config.h>
#include "igeometry_cooker.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}

namespace Attributes {
	class IGeometry;

	class GeometryCooker : public IGeometryCooker {
	public:
		void Cook(IGeometry* geometry, Graphics::IVertexArray* va, Graphics::IIndexArray* ia) override;
	private:
		void CookPositionNormalTangentBitangentTexture0(IGeometry* geometry, Graphics::IVertexArray*& va, Graphics::IIndexArray*& ia);
		void CookPositionNormal(IGeometry* mesh, Graphics::IVertexArray*& _vb, Graphics::IIndexArray*& _ib);
		void CookPosition(IGeometry* mesh, Graphics::IVertexArray*& _vb, Graphics::IIndexArray*& _ib);
		void CookPositionTexture0(IGeometry* mesh, Graphics::IVertexArray*& _vb, Graphics::IIndexArray*& _ib);
		void CookPositionNormalTexture0(IGeometry* mesh, Graphics::IVertexArray*& _vb, Graphics::IIndexArray*& _ib);
	};
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_COOKER