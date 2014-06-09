#ifndef _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_DIFFUSE
#define _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_DIFFUSE

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        class VsPerVertexLightingDiffuse : public Shader
		{
		public:
            VsPerVertexLightingDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
            unsigned uView;

			LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
		};
	}
}
PUNK_ENGINE_END

#endif