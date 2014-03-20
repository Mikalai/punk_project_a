#include "fs_gui.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderGUI::FragmentShaderGUI()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"gui_330.frag");
		}
	}
}
PUNK_ENGINE_END
