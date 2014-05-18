#ifndef _H_ICURVE
#define _H_ICURVE

#include <config.h>
#include <core/iobject.h>
#include <vector>

PUNK_ENGINE_BEGIN
namespace Math {
	
	class ISpline;

	DEFINE_PUNK_GUID(IID_ICurve, "F5B0CB90-C275-4D02-A3E6-2852C1A40FA1");

	class ICurve : public virtual Core::IObject {
	public:
		virtual void AddSpline(ISpline* value) = 0;
		virtual void AddSplines(const std::vector<ISpline*>& value) = 0;
		virtual float GetTotalLength() const = 0;
		virtual const Math::vec3 At(float t) = 0;
		virtual std::uint32_t GetSplinesCount() const = 0;
		virtual const ISpline* GetSpline(std::uint32_t index) const = 0;
		virtual void Clear() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICURVE