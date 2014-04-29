#include "gramm_shmidt.h"
#include "vec3.h"

PUNK_ENGINE_BEGIN
namespace Math {
	void GrammShmidtNormalization::OrthogonalizeAndNormalize(vec3& a, vec3& b, vec3& c) {
		a.Normalize();
		b = (b - b.Dot(a)*a).Normalized();
		c = (c - c.Dot(a)*a - c.Dot(b)*b).Normalized();
	}

	void GrammShmidtNormalization::Orthogonalize(vec3& a, vec3& b, vec3& c) {		
		b = (b - b.Dot(a)*a);
		c = (c - c.Dot(a)*a - c.Dot(b)*b);
	}
}
PUNK_ENGINE_END
