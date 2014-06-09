#ifndef VS_BUMP_DIFFUSE_COLOR_H
#define VS_BUMP_DIFFUSE_COLOR_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class VsBumpMappingDiffuseColor: public Shader
        {
        public:
            VsBumpMappingDiffuseColor();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uWorld;
            unsigned uViewWorld;
            unsigned uView;
            unsigned uProj;
            unsigned uNormalMatrix;
            unsigned uTextureMatrix;
            LightSourceShaderParameters uLight;
        };
    }
}
PUNK_ENGINE_END

#endif // VS_BUMP_DIFFUSE_COLOR_H
