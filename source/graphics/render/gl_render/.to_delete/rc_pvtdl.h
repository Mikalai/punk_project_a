//#ifdef USE_RC_PVRTDL

////	Render context per vertex texture diffuse lighting

//#ifndef RC_PVTDL_H
//#define RC_PVTDL_H

//#include "../../common/config.h"
//#include "gl_render_context.h"

//namespace Graphics
//{

//	namespace OpenGL
//	{
//		template<> class RenderContextPolicy<
//				ShaderCollection::VertexLightPerVertexTextureDiffuse,
//				ShaderCollection::FragmentLightPerVertexTextureDiffuse,
//				ShaderCollection::No> : public OpenGLRenderContext
//		{
//			unsigned uNormalMatrix;
//			unsigned uViewWorld;
//			unsigned uProjViewWorld;
//			unsigned uView;
//			unsigned uDiffuseColor;
//			unsigned uTextureMatrix;
//			unsigned uDiffuseMap;

//			unsigned uConstantAttenuation[MAX_LIGHTS];
//			unsigned uLinearAttenuation[MAX_LIGHTS];
//			unsigned uQuadricAttenuation[MAX_LIGHTS];
//			unsigned uMode[MAX_LIGHTS];
//			unsigned uLightPosition[MAX_LIGHTS];
//			unsigned uLightDiffuse[MAX_LIGHTS];
//			unsigned uSpotExponent[MAX_LIGHTS];
//			unsigned uType[MAX_LIGHTS];	//	0 - point, 1 - linear
//			unsigned uLightDirection[MAX_LIGHTS];


//		public:
//			RenderContextPolicy();
//			virtual void InitUniforms() override;
//			virtual void BindParameters(const CoreState& params) override;
//			virtual int64_t GetRequiredAttributesSet() const= 0;
//		};
//	}

//}

//#endif // RC_PVTDL_H

//#endif	//	USE_RC_PVRTDL
