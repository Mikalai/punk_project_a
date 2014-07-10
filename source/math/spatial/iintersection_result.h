#ifndef _H_IINTERSECTION_RESULT
#define _H_IINTERSECTION_RESULT

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {

	DECLARE_PUNK_GUID(IID_IIntersectionResult, "4B66AE62-DC9D-4C09-BADB-8CA7780A6F8E");
	DECLARE_PUNK_GUID(CLSID_IntersectionResult, "4B66AE62-DC9D-4C09-BADB-8CA7780A6F8E");

	enum class IntersectionHint : std::uint64_t {
		No = 0x0, 
		BoundingBox = 0x1, 
		BoundingSphere = 0x2, 
		BoundingRectangle = 0x1, 
		BoundingCircle = 0x2
	};

	inline IntersectionHint operator | (const IntersectionHint& l, const IntersectionHint& r) {
		return IntersectionHint((std::uint64_t)l | (std::uint64_t)r);
	}

	struct Intersection {
		IntersectionHint Hint{ IntersectionHint::No };
		Math::vec3 Point{ 0, 0, 0 };
	};

	class IIntersectionResult : public Core::IObject {
	public:
		virtual bool HasIntersection() const = 0;
		virtual void AddIntersectionPoint(const Math::vec3& value) = 0;
		virtual void AddIntersectionPoint(const Math::vec3& value, IntersectionHint hint) = 0;
		virtual std::uint32_t GetIntersectionsCount() const = 0;
		virtual const Intersection& GetIntersection(std::uint32_t index) = 0;
	};

}
PUNK_ENGINE_END

#endif	//	_H_IINTERSECTION_RESULT