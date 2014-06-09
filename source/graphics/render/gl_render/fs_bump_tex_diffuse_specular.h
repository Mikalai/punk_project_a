#ifndef FS_BUMP_TEX_DIFFUSE_SPECULAR_H
#define FS_BUMP_TEX_DIFFUSE_SPECULAR_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsBumpMappingTextureDiffuseSpecular : public Shader
        {
        public:
            FsBumpMappingTextureDiffuseSpecular();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            MaterialShaderParameters uMaterial;
            LightSourceShaderParameters uLight;
            unsigned uNormalMap;
        };
    }
}
PUNK_ENGINE_END

#endif // FS_BUMP_TEX_DIFFUSE_SPECULAR_H
