#include "vs_gui.h"
#include "../../../../../system/environment.h"

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