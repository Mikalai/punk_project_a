#include "vs_gui.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderGUI::VertexShaderGUI()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"gui_330.vert");
		}
	}
}
PUNK_ENGINE_END
