#include "vs_terrain.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderTerrain::VertexShaderTerrain()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"terrain_330.vert");
		}
	}
}
PUNK_ENGINE_END
