#ifndef _H_PUNK_VIRTUAL_POINT_LIGHT
#define _H_PUNK_VIRTUAL_POINT_LIGHT

#include "ilight.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DEFINE_PUNK_GUID(IID_IPointLight, "A47DC1CE-9234-4A05-9456-114A1363DC02");

	class IPointLight : public virtual ILight {	
	public:		
		virtual void SetDistance(float value) = 0;
		virtual float GetDistance() const = 0;
		virtual void SetLinearAttenuation(float value) = 0;
		virtual float GetLinearAttenuation() const = 0;
		virtual void SetQuadraticAttenuation(float value) = 0;
		virtual float GetQuadraticAttenuation() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_POINT_LIGHT
