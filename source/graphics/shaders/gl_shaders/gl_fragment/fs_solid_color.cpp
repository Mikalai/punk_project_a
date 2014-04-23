#include "fs_solid_color.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		FsSolid::FsSolid()
			: Shader(ShaderType::Fragment)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
						 + GetShaderFile(ShaderCollection::FragmentSolidColor));
		}

		void FsSolid::InitUniforms()
		{
			uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
		}

		void FsSolid::BindParameters(const CoreState& params)
		{
          //  GL_CALL(glPolygonOffset(1.0f, 4096.0f));
			m_rc->SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);
		}

		int64_t FsSolid::GetRequiredAttributesSet() const
		{
			return 0;
		}
	}
}
PUNK_ENGINE_END