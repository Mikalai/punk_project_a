#include "fs_solid_textured.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        FsSolidTextured3D::FsSolidTextured3D()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentSolidTextured));
        }

        void FsSolidTextured3D::InitUniforms()
        {
            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
            uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
        }

        void FsSolidTextured3D::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
            if (params.texture_state->m_diffuse_slot[0] != -1)
                m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);
        }

        int64_t FsSolidTextured3D::GetRequiredAttributesSet() const
        {
            return 0;
        }
	}
}
PUNK_ENGINE_END
