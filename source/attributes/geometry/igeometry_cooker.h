#ifndef _H_IGEOMETRY_COOKER
#define _H_IGEOMETRY_COOKER

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}
namespace Attributes {
	
	class IGeometry;

	DECLARE_PUNK_GUID(IID_IGeometryCooker, "F72357C2-133F-4B8D-9E4E-060372691779");

	class IGeometryCooker : public Core::IObject {
	public:
		virtual void EnableTangetBitangentGeneration(bool flag) = 0;
		virtual bool IsEnabledTangentBitangentGeneration() const = 0;
		virtual void Cook(Core::Pointer<IGeometry> geometry, Core::Pointer<Graphics::IVertexArray>& va, Core::Pointer<Graphics::IIndexArray>& ia) = 0;
	};

	using IGeometryCookerPointer = Core::Pointer < IGeometryCooker > ;
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY_COOKER