#ifndef FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
#define FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsPerFragmentLightingDiffuse : public Shader
        {
        public:
            FsPerFragmentLightingDiffuse();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseColor;
            unsigned uView;
            LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
        };
    }
}
PUNK_ENGINE_END

#endif // FS_PER_FRAGMENT_LIGHTING_DIFFUSE_H
