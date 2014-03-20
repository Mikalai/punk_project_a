#ifndef FS_BUMP_DIFFUSE_COLOR_SPECULAR_H
#define FS_BUMP_DIFFUSE_COLOR_SPECULAR_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsBumpMappingDiffuseColorSpecular : public Shader
        {
        public:
            FsBumpMappingDiffuseColorSpecular();
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

#endif // FS_BUMP_DIFFUSE_COLOR_SPECULAR_H
