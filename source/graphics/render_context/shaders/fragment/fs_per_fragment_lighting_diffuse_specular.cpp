#include <sstream>
#include "fs_per_fragment_lighting_diffuse_specular.h"
#include "../gl_shader_type.h"
#include "../../../../../system/environment.h"
#include "../../../../../system/folder.h"
#include "../../../../../system/binary_file.h"
#include "../../rc_dynamic.h"

namespace Gpu
{
    namespace OpenGL
    {
        FsPerFragmentLightingDiffuseSpecular::FsPerFragmentLightingDiffuseSpecular()
            : Shader{ShaderType::Fragment}
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            const char* names[] = {"/light.glsl", "/material.glsl"};
            CookFromFileWithHeaders(GetShaderFile(ShaderCollection::FragmentLightPerFragmentDiffuseSpecular), 2, names);
        }

        void FsPerFragmentLightingDiffuseSpecular::InitUniforms()
        {
            uCameraWorldPosition = m_rc->GetUniformLocation("uCameraWorldPosition");
            uView = m_rc->GetUniformLocation("uView");
            uMaterial = m_rc->GetUniformaMaterialLocation("uMaterial");

            for (int i = 0; i != MAX_LIGHTS; ++i)
            {
                std::stringstream stream;
                stream << "uLight[" << i << "]";
                uLight[i] = m_rc->GetUniformLightLocation(stream.str().c_str());
            }
        }

        void FsPerFragmentLightingDiffuseSpecular::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformVector3f(uCameraWorldPosition, params.view_state->m_camera_position);                                
            m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

            m_rc->SetUniformMaterial(uMaterial, params.batch_state->m_material);

            for (unsigned i = 0; i != params.light_state->m_used_lights; ++i)
            {
                m_rc->SetUniformLight(uLight[i], params.light_state->m_lights[i]);
            }
        }

        int64_t FsPerFragmentLightingDiffuseSpecular::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
