#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING_SOLID
#define _H_PUNK_OPENGL_VERTEX_SHADER_SKINNING_SOLID

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class VsSkinningDepth : public Shader
        {
        public:
            VsSkinningDepth();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uProjViewWorld;
            unsigned uBones[BaseState::MAX_BONES];
        };
    }
}
PUNK_ENGINE_END

#endif
