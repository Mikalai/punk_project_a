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

            unsigned uLightPosition[BaseState::MAX_LIGHTS];
            unsigned uLightDirection[BaseState::MAX_LIGHTS];
            unsigned uLightDiffuse[BaseState::MAX_LIGHTS];

            unsigned uConstantAttenuation[BaseState::MAX_LIGHTS];
            unsigned uLinearAttenuation[BaseState::MAX_LIGHTS];
            unsigned uQuadricAttenuation[BaseState::MAX_LIGHTS];

            unsigned uMode[BaseState::MAX_LIGHTS]; //	0 - Constant, 1 - Linear, 2 - Quadric
            unsigned uSpotExponent[BaseState::MAX_LIGHTS];
            unsigned uType[BaseState::MAX_LIGHTS];	//	0 - point, 1 - linear

		};
	}
}
PUNK_ENGINE_END

#endif
