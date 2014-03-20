#include <sstream>
#include "fs_per_fragment_lighting_diffuse.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        FsPerFragmentLightingDiffuse::FsPerFragmentLightingDiffuse()
            : Shader{ShaderType::Fragment}
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            const char* names[] = {"/light.glsl"};
            CookFromFileWithHeaders(GetShaderFile(ShaderCollection::FragmentLightPerFragmentDiffuse), 1, names);
        }

        void FsPerFragmentLightingDiffuse::InitUniforms()
        {

            uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
            uView = m_rc->GetUniformLocation("uView");
            for (int i = 0; i != BaseState::MAX_LIGHTS; ++i)
            {
                std::stringstream stream;
                stream << "uLight[" << i << "]";
                uLight[i] = m_rc->GetUniformLightLocation(stream.str().c_str());
            }
        }

        void FsPerFragmentLightingDiffuse::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

            for (unsigned i = 0; i != params.light_state->m_used_lights; ++i)
            {
                m_rc->SetUniformLight(uLight[i], params.light_state->m_lights[i]);
            }
        }

        int64_t FsPerFragmentLightingDiffuse::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
PUNK_ENGINE_END

