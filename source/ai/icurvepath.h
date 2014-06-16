#ifndef _H_ICURVE_PATH
#define _H_ICURVE_PATH

#include <config.h>
#include <math/icurve.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace AI {

	DECLARE_PUNK_GUID(IID_ICurvePath, "7B1EBE2B-6E2E-467A-BE39-EF7890622C41");

	class ICurvePath : public Math::ICurve {
	public:
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICURVE_PATH