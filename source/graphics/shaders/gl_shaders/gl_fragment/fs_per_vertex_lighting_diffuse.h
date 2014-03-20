#ifndef _H_PUNK_OPENGL_FRAGMENT_PER_VERTEX_LIGHTING_DIFFUSE
#define _H_PUNK_OPENGL_FRAGMENT_PER_VERTEX_LIGHTING_DIFFUSE

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        class FsPerVertexLightingDiffuse : public Shader
		{
		public:
            FsPerVertexLightingDiffuse();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
            unsigned uDiffuseColor;
		};
	}
}
PUNK_ENGINE_END

#endif
