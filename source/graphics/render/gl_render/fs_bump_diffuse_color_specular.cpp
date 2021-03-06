#include "fs_bump_diffuse_color_specular.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        FsBumpMappingDiffuseColorSpecular::FsBumpMappingDiffuseColorSpecular()
            : Shader(ShaderType::Fragment)
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            const char* names[] = {"/light.glsl", "/material.glsl"};
            CookFromFileWithHeaders(GetShaderFile(ShaderCollection::FragmentBumpMappingDiffuseColorSpecular), 2, names);
        }

        void FsBumpMappingDiffuseColorSpecular::InitUniforms()
        {
            uMaterial = m_rc->GetUniformaMaterialLocation("uMaterial");
            uLight = m_rc->GetUniformLightLocation("uLight");
            uNormalMap = m_rc->GetUniformLocation("uNormalMap");
        }

        void FsBumpMappingDiffuseColorSpecular::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformMaterial(uMaterial, params.batch_state->m_material);
            m_rc->SetUniformLight(uLight, params.light_state->m_lights[0]);
            m_rc->SetUniformInt(uNormalMap, params.texture_state->m_normal_map_slot);
        }

        int64_t FsBumpMappingDiffuseColorSpecular::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
PUNK_ENGINE_END

