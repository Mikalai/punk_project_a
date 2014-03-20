#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D
#define _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        class VsSolid : public Shader
		{
		public:
            VsSolid();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:            
			unsigned uProjViewWorld;
		};
	}
}
PUNK_ENGINE_END

#endif
