#ifndef VS_SOLID_VERTEX_COLOR_H
#define VS_SOLID_VERTEX_COLOR_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		class VsSolidVertexColor : public Shader
		{
		public:
			VsSolidVertexColor();

			virtual void InitUniforms() override;
			virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

		private:
			unsigned uProjViewWorld;
		};
	}
}
PUNK_ENGINE_END

#endif // VS_SOLID_VERTEX_COLOR_H
