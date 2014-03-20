#ifndef SHADOW_SINGLE_H
#define SHADOW_SINGLE_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsShadowSingle : public Shader
        {
        public:
            FsShadowSingle();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseMap;
            unsigned uFarDistance;
            unsigned uShadowTextureArray;
            unsigned uShadowMatrix[4];
            unsigned uFar;
            unsigned uNear;
            FogShaderParameters uFog;
        };
    }
}
PUNK_ENGINE_END

#endif // SHADOW_SINGLE_H
