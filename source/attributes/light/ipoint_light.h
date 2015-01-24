#ifndef _H_PUNK_VIRTUAL_POINT_LIGHT
#define _H_PUNK_VIRTUAL_POINT_LIGHT

#include <system/factory/interface.h>
#include <math/tuple.h>
#include <core/object.h>
#include "ilight.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IPointLight, "A47DC1CE-9234-4A05-9456-114A1363DC02");
	DECLARE_PUNK_GUID(IID_IPoint, "2C2C7139-D9AC-4918-A26D-8EEE414A91B6");
	DECLARE_PUNK_GUID(CLSID_Point, "1B00D83F-5A5D-459E-ACA1-24933126C3C2");

	class IPointLight : public ILight {	
	public:		
		virtual void SetDistance(float value) = 0;
		virtual float GetDistance() const = 0;
		virtual void SetLinearAttenuation(float value) = 0;
		virtual float GetLinearAttenuation() const = 0;
		virtual void SetQuadraticAttenuation(float value) = 0;
		virtual float GetQuadraticAttenuation() const = 0;
	};

	class IPoint : public Core::IObject {
	public:
		virtual void SetColor(const Math::Color3& value) = 0;
		virtual const Math::Color3 GetColor() const = 0;
		virtual void SetConstantAttenuation(const Math::realf& value) = 0;
		virtual const Math::realf GetConstantAttenuation() const = 0;
		virtual void SetLinearAttenuation(const Math::realf& value) = 0;
		virtual const Math::realf GetLinearAttenuation() const = 0;
		virtual void SetQuadraticsAttenuation(const Math::realf& value) = 0;
		virtual const Math::realf GetQuadraticsAttenuation() const = 0;
		virtual void SetZFar(const Math::realf& value) = 0;
		virtual const Math::realf GetZFar() = 0;
	};

	using IPointPtr = Core::Pointer < IPoint > ;

	inline IPointPtr NewPoint() {
		return System::CreateInstancePtr<IPoint>(CLSID_Point, IID_IPoint);
	}

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_POINT_LIGHT
