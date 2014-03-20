#ifndef VS_DEPTH_H
#define VS_DEPTH_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class VsDepth : public Shader
        {
        public:
            VsDepth();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
        };
    }
}
PUNK_ENGINE_END

#endif // VS_DEPTH_H
