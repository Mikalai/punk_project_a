#ifndef _H_ILIGHT
#define _H_ILIGHT

#include <config.h>
#include <math/vec3.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ILight, "37CE363B-3A53-4903-820C-00A3333371D1");

	class ILight : public Core::IObject{
	public:
		virtual void SetEnergy(float value) = 0;
		virtual float GetEnergy() const = 0;
		virtual void SetDiffuseColor(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetDiffuseColor() const = 0;
		virtual void SetSpecularColor(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetSpecularColor() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ILIGHT