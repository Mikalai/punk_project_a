#include "vs_depth.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        VsDepth::VsDepth()
            : Shader(ShaderType::Vertex)
        {
            System::Folder f;
            f.Open(System::Environment::Instance()->GetShaderFolder());
            CookFromFile(GetShaderFile(ShaderCollection::VertexDepth));
            f.Close();
        }

        void VsDepth::InitUniforms()
        {
            uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
        }

        void VsDepth::BindParameters(const CoreState& params)
        {
            const Math::mat4 m = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
            m_rc->SetUniformMatrix4f(uProjViewWorld, m);
        }

        int64_t VsDepth::GetRequiredAttributesSet() const
        {
            return VertexComponent::Position::Value();
        }
    }
}
PUNK_ENGINE_END
