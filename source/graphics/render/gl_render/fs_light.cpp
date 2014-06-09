#include "fs_light.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderLight::FragmentShaderLight()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"per_vertex_lighting_330.frag");
		}
	}
}
PUNK_ENGINE_END
