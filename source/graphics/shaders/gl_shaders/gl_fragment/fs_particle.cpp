#include "fs_particle.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderParticle::FragmentShaderParticle()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.frag");
		}
	}
}
PUNK_ENGINE_END
