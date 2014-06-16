#include "fs_painter.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FragmentShaderPainter::FragmentShaderPainter()
            : Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"painter_330.frag");
		}
	}
}
PUNK_ENGINE_END
