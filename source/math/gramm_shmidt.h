#ifndef _H_GRAM_SHMIDT_NORMALIZATION
#define _H_GRAM_SHMIDT_NORMALIZATION

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class vec3;
	class PUNK_ENGINE_API GrammShmidtNormalization {
	public:
		static void Orthogonalize(vec3& a, vec3& b, vec3& c);
		static void OrthogonalizeAndNormalize(vec3& a, vec3& b, vec3& c);
	};
}
PUNK_ENGINE_END

#endif	//	_H_GRAM_SHMIDT_NORMALIZATION