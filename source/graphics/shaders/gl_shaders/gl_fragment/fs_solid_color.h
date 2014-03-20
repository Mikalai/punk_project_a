#ifndef _H_PUNK_OPENGL_SHADER_SOLID_COLOR
#define _H_PUNK_OPENGL_SHADER_SOLID_COLOR

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		class FsSolid : public Shader
		{
		public:
			FsSolid();

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
