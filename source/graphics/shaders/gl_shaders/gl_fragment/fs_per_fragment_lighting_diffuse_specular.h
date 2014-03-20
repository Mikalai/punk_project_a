#ifndef FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H
#define FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsPerFragmentLightingDiffuseSpecular : public Shader
        {
        public:
            FsPerFragmentLightingDiffuseSpecular();

        private:

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uView;
            unsigned uCameraWorldPosition;
            MaterialShaderParameters uMaterial;
            LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
        };
    }
}
PUNK_ENGINE_END

#endif // FS_PER_FRAGMENT_LIGHTING_DIFFUSE_SPECULAR_H
