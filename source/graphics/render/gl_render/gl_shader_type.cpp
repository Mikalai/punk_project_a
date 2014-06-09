#include <utility>
#include <graphics/error/module.h>
#include "gl_shader_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		PUNK_ENGINE_LOCAL GLenum ConvertShaderTypeToOpenGL(ShaderType type) {
			switch (type)
			{
			case ShaderType::Bad:
				return GL_NONE;
			case ShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case ShaderType::Fragment:
				return GL_FRAGMENT_SHADER;
			case ShaderType::Geometry:
				return GL_GEOMETRY_SHADER;
			}
		}

		typedef std::pair<RenderContextType, const wchar_t*> ShaderFile;

		static const ShaderFile g_vertex_shaders[] = {
			ShaderFile(RenderContextType::NoRender, L""),
			ShaderFile(RenderContextType::NoLightSolidColor, L"solid_color_3d_330.vert")
		};
		/*ShaderFile(RenderContextType::BVertexBumpMapping, L"bump_330.vert"),
		ShaderFile(RenderContextType::VertexBumpMappingShadowMap, L"bump_330_shadow_map.vert"),
		ShaderFile(RenderContextType::FragmentBumpMapping, L"bump_330.frag"),
		ShaderFile(RenderContextType::FragmentBumpMappingShadowMap, L"bump_330_shadow_map.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingDiffuseColor, L"bump_diffuse_color_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingDiffuseColor, L"bump_diffuse_color_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingDiffuseColorSpecular, L"bump_diffuse_color_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingDiffuseColorSpecular, L"bump_diffuse_color_specular_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingTextureDiffuse, L"bump_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingTextureDiffuse, L"bump_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingTextureDiffuseSpecular, L"bump_tex_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingTextureDiffuseSpecular, L"bump_tex_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexSolidColor, L"solid_color_3d_330.vert"),
		ShaderFile(RenderContextType::FragmentSolidColor, L"solid_color_3d_330.frag"),
		ShaderFile(RenderContextType::VertexSolidVertexColor, L"solid_vertex_color.vert"),
		ShaderFile(RenderContextType::FragmentSolidVertexColor, L"solid_vertex_color.frag"),
		ShaderFile(RenderContextType::VertexSolidTextured, L"solid_textured_330.vert"),
		ShaderFile(RenderContextType::FragmentSolidTextured, L"solid_textured_330.frag"),
		ShaderFile(RenderContextType::FragmentSolidTextured2DArray, L"solid_texture_2d_array.frag"),
		ShaderFile(RenderContextType::VertexLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.vert"),
		ShaderFile(RenderContextType::VertexLightPerVertexDiffuseSpecular, L"per_vertex_lighting_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerVertexDiffuseSpecular, L"per_vertex_lighting_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.vert"),
		ShaderFile(RenderContextType::VertexLightPerFragmentDiffuseSpecular, L"per_fragment_lighting_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentDiffuseSpecular, L"per_fragment_lighting_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentTextureDiffuseSpecular, L"per_fragment_lighting_tex_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentTextureDiffuseSpecular, L"per_fragment_lighting_tex_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::VertexSkinningBump, L"skinning_bump_330.vert"),
		ShaderFile(RenderContextType::VertexSkinningDepth, L"skinning_depth_330.vert"),
		ShaderFile(RenderContextType::FragmentTextSolidColor, L"text_color_330.frag"),
		ShaderFile(RenderContextType::FragmentDepth, L"depth.frag"),
		ShaderFile(RenderContextType::VertexDepth, L"depth.vert"),
		ShaderFile(RenderContextType::VsPerVertexDiffuseLightingShadowSimple, L"per_vertex_lighting_diffuse_simple_shadow.vert"),
		ShaderFile(RenderContextType::FsPerVertexDiffuseLightingShadowSimple, L"per_vertex_lighting_diffuse_simple_shadow.frag"),
		ShaderFile(RenderContextType::FragmentShadowSingle, L"shadow_single.frag"),
		ShaderFile(RenderContextType::No, L"")
		};*/

		static const ShaderFile g_fragment_shaders[] = {
			ShaderFile(RenderContextType::NoRender, L""),
			ShaderFile(RenderContextType::NoLightSolidColor, L"solid_color_3d_330.frag")
		};

		/*ShaderFile(RenderContextType::VertexBumpMapping, L"bump_330.vert"),
		ShaderFile(RenderContextType::VertexBumpMappingShadowMap, L"bump_330_shadow_map.vert"),
		ShaderFile(RenderContextType::FragmentBumpMapping, L"bump_330.frag"),
		ShaderFile(RenderContextType::FragmentBumpMappingShadowMap, L"bump_330_shadow_map.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingDiffuseColor, L"bump_diffuse_color_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingDiffuseColor, L"bump_diffuse_color_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingDiffuseColorSpecular, L"bump_diffuse_color_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingDiffuseColorSpecular, L"bump_diffuse_color_specular_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingTextureDiffuse, L"bump_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingTextureDiffuse, L"bump_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::VertexBumpMappingTextureDiffuseSpecular, L"bump_tex_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentBumpMappingTextureDiffuseSpecular, L"bump_tex_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexSolidColor, L"solid_color_3d_330.vert"),
		ShaderFile(RenderContextType::FragmentSolidColor, L"solid_color_3d_330.frag"),
		ShaderFile(RenderContextType::VertexSolidVertexColor, L"solid_vertex_color.vert"),
		ShaderFile(RenderContextType::FragmentSolidVertexColor, L"solid_vertex_color.frag"),
		ShaderFile(RenderContextType::VertexSolidTextured, L"solid_textured_330.vert"),
		ShaderFile(RenderContextType::FragmentSolidTextured, L"solid_textured_330.frag"),
		ShaderFile(RenderContextType::FragmentSolidTextured2DArray, L"solid_texture_2d_array.frag"),
		ShaderFile(RenderContextType::VertexLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.vert"),
		ShaderFile(RenderContextType::VertexLightPerVertexDiffuseSpecular, L"per_vertex_lighting_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerVertexDiffuse, L"per_vertex_lighting_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerVertexDiffuseSpecular, L"per_vertex_lighting_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.vert"),
		ShaderFile(RenderContextType::VertexLightPerFragmentDiffuseSpecular, L"per_fragment_lighting_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentDiffuse, L"per_fragment_lighting_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentDiffuseSpecular, L"per_fragment_lighting_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerVertexTextureDiffuse, L"per_vertex_lighting_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.vert"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentTextureDiffuse, L"per_fragment_lighting_tex_diffuse_330.frag"),
		ShaderFile(RenderContextType::FragmentLightPerFragmentTextureDiffuseSpecular, L"per_fragment_lighting_tex_diffuse_specular_330.frag"),
		ShaderFile(RenderContextType::VertexLightPerFragmentTextureDiffuseSpecular, L"per_fragment_lighting_tex_diffuse_specular_330.vert"),
		ShaderFile(RenderContextType::VertexSkinningBump, L"skinning_bump_330.vert"),
		ShaderFile(RenderContextType::VertexSkinningDepth, L"skinning_depth_330.vert"),
		ShaderFile(RenderContextType::FragmentTextSolidColor, L"text_color_330.frag"),
		ShaderFile(RenderContextType::FragmentDepth, L"depth.frag"),
		ShaderFile(RenderContextType::VertexDepth, L"depth.vert"),
		ShaderFile(RenderContextType::VsPerVertexDiffuseLightingShadowSimple, L"per_vertex_lighting_diffuse_simple_shadow.vert"),
		ShaderFile(RenderContextType::FsPerVertexDiffuseLightingShadowSimple, L"per_vertex_lighting_diffuse_simple_shadow.frag"),
		ShaderFile(RenderContextType::FragmentShadowSingle, L"shadow_single.frag"),
		ShaderFile(RenderContextType::No, L"")
		};*/

		PUNK_ENGINE_LOCAL const Core::String GetShaderFile(RenderContextType render, ShaderType type)
		{
			const wchar_t* error = L"";
			if (type == ShaderType::Vertex)
			{
				for (auto it : g_vertex_shaders)
				{
					if (it.first == render)
						return it.second;
				}
			}
			else if (type == ShaderType::Fragment) {
				for (auto it : g_fragment_shaders) {
					if (it.first == render){
						return it.second;
					}
				}
			}
			throw Error::OpenGLException(L"Shader not found");
		}
	}
}
PUNK_ENGINE_END
