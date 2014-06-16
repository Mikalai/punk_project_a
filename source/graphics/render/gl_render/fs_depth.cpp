#include "fs_depth.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        FsDepth::FsDepth()
            : Shader(ShaderType::Fragment)
        {
            CookFromFile(System::Environment::Instance()->GetShaderFolder()
                         + GetShaderFile(ShaderCollection::FragmentDepth));
        }

        void FsDepth::InitUniforms()
        {            
        }

        void FsDepth::BindParameters(const CoreState& params)
        {           
        }

        int64_t FsDepth::GetRequiredAttributesSet() const
        {
            return 0;
        }
    }
}
PUNK_ENGINE_END
