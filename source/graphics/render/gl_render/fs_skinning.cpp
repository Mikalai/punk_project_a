#include "fs_skinning.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderSkinning::FragmentShaderSkinning()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"skinning_330.frag");
		}
	}
}
PUNK_ENGINE_END
