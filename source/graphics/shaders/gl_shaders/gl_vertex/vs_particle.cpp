#include "vs_particle.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderParticle::VertexShaderParticle()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"particle_330.vert");
		}
	}
}
PUNK_ENGINE_END
