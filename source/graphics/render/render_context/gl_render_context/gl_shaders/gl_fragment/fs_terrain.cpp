#include "fs_terrain.h"
#include "../../../../../system/environment.h"

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