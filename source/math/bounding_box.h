#ifndef _H_PUNK_MATH_BOUNDING_BOX
#define _H_PUNK_MATH_BOUNDING_BOX

#include <cstdint>
#include <config.h>
#include "vec3.h"
#include "plane.h"

PUNK_ENGINE_BEGIN
namespace Math {
	
	class BoundingSphere;

	class PUNK_ENGINE_API BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const BoundingBox& value);
		BoundingBox& operator = (const BoundingBox& value);
		void Create(const vec3* points, std::uint32_t count);
		const vec3& GetR() const;
		const vec3& GetS() const;
		const vec3& GetT() const;
		const vec3& GetCenter() const;
		const vec3& GetMassCenter() const;
		const vec3& GetMinCorner() const;
		const Plane& GetPlane(int index) const;
		const BoundingSphere ToBoundingSphere();

	private:

		struct Core {
			//	natural center
			vec3 m_center_of_mass;
			//	bbox center
			vec3 m_center;
			vec3 m_min_corner;
			//	natural axes
			vec3 m_r;
			vec3 m_s;
			vec3 m_t;
			//	natural planes of the bbox
			Plane m_plane[6];
		};

		Core m_core;


		friend PUNK_ENGINE_API const BoundingBox operator * (const mat4& m, const BoundingBox& bbox);
	};

	PUNK_ENGINE_API const BoundingBox operator * (const mat4& m, const BoundingBox& bbox);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_BOUNDING_BOX
