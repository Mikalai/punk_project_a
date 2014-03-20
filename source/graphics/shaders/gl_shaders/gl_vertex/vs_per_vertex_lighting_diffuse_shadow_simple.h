#ifndef VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
#define VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        //  Vertex shader: per vertex lighting with diffuse texture and single shadowing
        class VsPerVertexLightingDiffuseShadowSimple : public Shader
        {
        public:
            VsPerVertexLightingDiffuseShadowSimple();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProj;
            unsigned uView;
            unsigned uWorld;
            unsigned uProjViewWorld;            
            unsigned uNormalMatrix;
            unsigned uDiffuseColor;
            unsigned uLightsCount;
            LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
        };
    }
}
PUNK_ENGINE_END

#endif // VS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
