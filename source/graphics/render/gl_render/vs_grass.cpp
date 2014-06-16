#include "vs_grass.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderGrass::VertexShaderGrass()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"grass_330.vert");
		}
	}
}
PUNK_ENGINE_END
