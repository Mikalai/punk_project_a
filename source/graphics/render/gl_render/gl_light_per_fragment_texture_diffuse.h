#ifndef _H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_TEXTURE_DIFFUSE
#define _H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_TEXTURE_DIFFUSE

#include <sstream>
#include <graphics/primitives/vertex.h>
#include "gl_shader.h"
#include "gl_shader_cooker.h"
#include "gl_render_context_base.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		template<>
		struct ShaderAspect < RenderContextType::LightPerFragmentTextureDiffuse, ShaderType::Vertex > {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc } {}

			void InitUniforms()
			{
				uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
				uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
				uViewWorld = m_rc->GetUniformLocation("uViewWorld");
				uTextureMatrix = m_rc->GetUniformLocation("uTextureMatrix");
			}

			void BindParameters(const CoreState& params)
			{
				const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
				const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
				const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
				m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
				m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
				m_rc->SetUniformMatrix4f(uViewWorld, view_world);
				m_rc->SetUniformMatrix4f(uTextureMatrix, params.batch_state->m_texture_matrix);
			}

			int64_t GetRequiredAttributesSet() const
			{
				return VertexComponent::Position::Value()
					| VertexComponent::Normal::Value()
					| VertexComponent::Texture0::Value();
			}

			GLuint GetIndex() {
				return m_index;
			}

			void Cook() {
				System::Folder f;
				f.Open(System::Environment::Instance()->GetShaderFolder());				
					
				m_index = ShaderCooker::CookFromFile(ShaderType::Vertex, 
					GetShaderFile(RenderContextType::LightPerFragmentTextureDiffuse, ShaderType::Vertex));
			}

			GLuint m_index;
			GlRenderContextBase* m_rc;
			unsigned uNormalMatrix;
			unsigned uViewWorld;
			unsigned uProjViewWorld;
			unsigned uTextureMatrix;
			unsigned uDiffuseMap;
		};

		template<>
		struct ShaderAspect<RenderContextType::LightPerFragmentTextureDiffuse, ShaderType::Fragment> {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc }
			{}

			void InitUniforms()
			{
				uView = m_rc->GetUniformLocation("uView");
				uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
				uDiffuseMap = m_rc->GetUniformLocation("uDiffuseMap");
				for (int i = 0; i != BaseState::MAX_LIGHTS; ++i)
				{
					std::stringstream stream;
					stream << "uLight[" << i << "]";
					uLight[i] = m_rc->GetUniformLightLocation(stream.str().c_str());
				}
			}

			void BindParameters(const CoreState& params)
			{
				m_rc->SetUniformVector4f(uDiffuseColor, params.batch_state->m_material.m_diffuse_color);
				m_rc->SetUniformInt(uDiffuseMap, params.texture_state->m_diffuse_slot[0]);

				for (unsigned i = 0; i != params.light_state->m_used_lights; ++i)
				{
					m_rc->SetUniformLight(uLight[i], params.light_state->m_lights[i]);
				}
			}

			int64_t GetRequiredAttributesSet() const
			{
				return 0;
			}

			GLuint GetIndex() {
				return m_index;
			}

			void Cook() {
				System::Folder f;
				f.Open(System::Environment::Instance()->GetShaderFolder());
				const char* names[] = { "/light.glsl" };
				m_index = ShaderCooker::CookFromFileWithHeaders(ShaderType::Fragment,
					GetShaderFile(RenderContextType::LightPerFragmentTextureDiffuse, ShaderType::Fragment), 1, names);
			}

			GLuint m_index{ 0 };
			GlRenderContextBase* m_rc;
			unsigned uView;
			unsigned uDiffuseColor;
			unsigned uDiffuseMap;
			LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_TEXTURE_DIFFUSE