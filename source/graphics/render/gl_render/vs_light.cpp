#include "vs_light.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VertexShaderLight::VertexShaderLight()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder() + L"per_vertex_lighting_330.vert");
		}
	}
}
PUNK_ENGINE_END
