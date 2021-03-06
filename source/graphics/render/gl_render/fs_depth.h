#ifndef FS_DEPTH_H
#define FS_DEPTH_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsDepth : public Shader
        {
        public:
            FsDepth();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:            
        };
    }
}
PUNK_ENGINE_END

#endif // FS_DEPTH_H
