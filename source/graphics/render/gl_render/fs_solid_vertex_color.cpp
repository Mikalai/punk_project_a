#include "fs_solid_vertex_color.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FsSolidVertexColor::FsSolidVertexColor()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidVertexColor));
		}

		void FsSolidVertexColor::InitUniforms()
		{
		}

        void FsSolidVertexColor::BindParameters(const CoreState&)
		{
		}

		int64_t FsSolidVertexColor::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
PUNK_ENGINE_END
