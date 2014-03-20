#ifndef _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_TEXTURE_DIFFUSE
#define _H_PUNK_OPENGL_PER_VERTEX_LIGHTING_TEXTURE_DIFFUSE

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        class VsPerVertexLightingTextureDiffuse : public Shader
		{
		public:
            VsPerVertexLightingTextureDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uNormalMatrix;
            unsigned uViewWorld;
            unsigned uProjViewWorld;
            unsigned uView;
			unsigned uTextureMatrix;

            LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
		};
	}
}
PUNK_ENGINE_END

#endif
