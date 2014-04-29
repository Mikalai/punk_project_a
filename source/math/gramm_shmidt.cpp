#include "gramm_shmidt.h"
#include "vec3.h"

PUNK_ENGINE_BEGIN
namespace Math {
	void GrammShmidtNormalization::Normalize(vec3& a, vec3& b, vec3& c) {
		a.Normalize();
		b = (b - b.Dot(a)*a).Normalized();
		c = (c - c.Dot(a)*a - c.Dot(b)*b).Normalized();
	}
}
PUNK_ENGINE_END
