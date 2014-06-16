#ifndef _H_PUNK_OPENGL_SHADER_SOLID_TEXTURED_ARRAY
#define _H_PUNK_OPENGL_SHADER_SOLID_TEXTURED_ARRAY

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsSolidTextured2DArray : public Shader
        {
        public:
            FsSolidTextured2DArray();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uMaps;
            unsigned uDiffuseColor;
            unsigned uLayer;
        };
    }
}
PUNK_ENGINE_END

#endif
