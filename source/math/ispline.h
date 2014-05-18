#ifndef H_ISPLINE
#define H_ISPLINE

#include <cstdint>
#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {

	DEFINE_PUNK_GUID(IID_ISpline, "25CBA834-CFC7-4CC9-86F9-A2981A21D604");

	class WeightedPoint;

	class ISpline : public virtual Core::IObject {
	public:
		virtual void AddPoint(const WeightedPoint& value) = 0;
		virtual void AddPoints(const std::vector<WeightedPoint>& value) = 0;
		virtual float GetTotalLength() const = 0;
		virtual const WeightedPoint At(float t) = 0;
		virtual std::uint32_t GetPointsCount() const = 0;
		virtual const WeightedPoint& GetPoint(int index) const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	H_ISPLINE