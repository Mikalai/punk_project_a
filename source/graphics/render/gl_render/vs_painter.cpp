#include "vs_painter.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderPainter::VertexShaderPainter()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"painter_330.vert");
		}
	}
}
PUNK_ENGINE_END
