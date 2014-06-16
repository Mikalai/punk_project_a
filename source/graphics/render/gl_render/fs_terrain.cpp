#include "fs_terrain.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderTerrain::FragmentShaderTerrain()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.frag");
		}
	}
}
PUNK_ENGINE_END
