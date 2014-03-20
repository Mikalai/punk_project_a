#ifndef _H_PUNK_OPENGL_SHADER_SOLID_TEXTURED
#define _H_PUNK_OPENGL_SHADER_SOLID_TEXTURED

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		class FsSolidTextured3D : public Shader
		{
		public:
			FsSolidTextured3D();            
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseMap;
            unsigned uDiffuseColor;
		};
	}
}
PUNK_ENGINE_END

#endif
