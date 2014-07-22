#include <set>
#include <cstdint>
#include <limits>
#include <utility>
#include <algorithm>
#include "min_max.h"
#include "vec2.h"
#include "mat2.h"
#include "mat3.h"
#include "relations.h"
#include "constants.h"
#include "root_find.h"
#include "vec3.h"
#include "sphere.h"
#include "triangle3d.h"
#include "line3d.h"
#include "line2d.h"
#include "polygon3d.h"
#include "plane.h"
#include "ellipsoid.h"
#include "portal.h"
#include "clip_space.h"
#include "bounding_box.h"
#include "convex_shape_mesh.h"
#include "ifrustum.h"
#include "triangle2d.h"
#include "frustum_plane.h"
#include "frustum_points.h"
#include "trigonometry.h"
#include "absolute_value.h"
#include "bounding_sphere.h"
#include "mat4.h"
#include "math_error.h"
#include "frustum_core.h"

PUNK_ENGINE_BEGIN
namespace Math {					

	//PUNK_ENGINE_API Relation CrossCircleTrianglesProjection(const std::vector<vec3>& point, const std::vector<ivec3>& faces, const Math::vec3& center, T radius)
	//{
	//	for (const Math::ivec3& f : faces)
	//	{
	//		const Math::vec3& p0 = point[f[0]];
	//		const Math::vec3& p1 = point[f[1]];
	//		const Math::vec3& p2 = point[f[2]];

	//		auto c = (p0 + p1 + p2) * 0.33333333f;
	//		if ((c - center).Length() < radius)
	//			return Relation::INTERSECT;
	//	}
	//	return Relation::NOT_INTERSECT;
	//}

	

	//                Relation Classify(const ivec2& p0, const ivec2 p1)
	//                {
	//                    ivec2 p2 = *this;
	//                    ivec2 a = p1 - p0;
	//                    ivec2 b = p2 - p0;
	//                    double sa = a.X() * b.Y() - b.X() - a.Y();
	//                    if (sa > 0.0)
	//                        return Relation::LEFT;
	//                    if (sa < 0.0)
	//                        return Relation::RIGHT;
	//                    if ((a.X() * b.X() < 0.0) || (a.Y() * b.Y() < 0.0))
	//                        return Relation::BACK;
	//                    if (a.Length() < b.Length())
	//                        return Relation::FRONT;
	//                    if (p0 == p2)
	//                        return Relation::START;
	//                    if (p1 == p2)
	//                        return Relation::END;
	//                    return Relation::BACK;
	//                }
	//            };
}
PUNK_ENGINE_END