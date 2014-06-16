#include "fs_grass.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderGrass::FragmentShaderGrass()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"grass_330.frag");
		}
	}
}
PUNK_ENGINE_END
