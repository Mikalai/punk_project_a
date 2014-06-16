#include "fs_solid_textured_2d_array.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        FsSolidTextured2DArray::FsSolidTextured2DArray()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentSolidTextured2DArray));
        }

        void FsSolidTextured2DArray::InitUniforms()
        {
            uLayer = m_rc->GetUniformLocation("uLayer");
            uMaps = m_rc->GetUniformLocation("uMaps");
        }

        void FsSolidTextured2DArray::BindParameters(const CoreState& params)
        {
            m_rc->SetUniformInt(uMaps, params.texture_state->m_texture_array_slot);
            m_rc->SetUniformFloat(uLayer, params.texture_state->m_texture_array_diffuse_map_layer[0]);
        }

        int64_t FsSolidTextured2DArray::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
PUNK_ENGINE_END
