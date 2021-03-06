#ifndef _H_PUNK_OPENGL_VERTEX_PER_VERTEX_LIGHTING
#define _H_PUNK_OPENGL_VERTEX_PER_VERTEX_LIGHTING

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        class VsPerVertexLighting : public Shader
		{
		public:
            VsPerVertexLighting();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
			virtual int64_t GetRequiredAttributesSet() const= 0;

		private:
            unsigned uNormalMatrix;
            unsigned uView;
            unsigned uWorld;
            unsigned uProj;
            unsigned uLightPosition;
            unsigned uDiffuse;

		};
	}
}
PUNK_ENGINE_END

#endif
