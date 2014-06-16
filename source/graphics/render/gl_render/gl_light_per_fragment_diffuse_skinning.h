#ifndef _H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_DIFFUSE_SKINNING
#define _H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_DIFFUSE_SKINNING

#include <sstream>
#include <algorithm>
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
		struct ShaderAspect < RenderContextType::LightPerFragmentDiffuseSkinning, ShaderType::Vertex > {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc } {}

			void InitUniforms()
			{
				uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
				uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
				uViewWorld = m_rc->GetUniformLocation("uViewWorld");
				for (int i = 0; i < BaseState::MAX_BONES; ++i) {
					std::stringstream stream;
					stream << "uBones[" << i << "]";
					uBones[i] = m_rc->GetUniformLocation(stream.str().c_str());
				}
			}

			void BindParameters(const CoreState& params)
			{
				const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
				const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
				const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
				m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
				m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
				m_rc->SetUniformMatrix4f(uViewWorld, view_world);

				for (int i = 0, max_i = BaseState::MAX_BONES; i < max_i; ++i) {
					m_rc->SetUniformMatrix4f(uBones[i], params.batch_state->m_bone_matrix[i]);
				}
			}

			int64_t GetRequiredAttributesSet() const
			{
				return VertexComponent::Position::Value()
					| VertexComponent::Normal::Value();
			}

			GLuint GetIndex() {
				return m_index;
			}

			void Cook() {
				System::Folder f;
				f.Open(System::Environment::Instance()->GetShaderFolder());
				m_index = ShaderCooker::CookFromFile(ShaderType::Vertex,
					GetShaderFile(RenderContextType::LightPerFragmentDiffuseSkinning, ShaderType::Vertex));
			}

			GLuint m_index;
			GlRenderContextBase* m_rc;
			unsigned uNormalMatrix;
			unsigned uViewWorld;
			unsigned uProjViewWorld;
			unsigned uBones[BaseState::MAX_BONES];
		};

		template<>
		struct ShaderAspect<RenderContextType::LightPerFragmentDiffuseSkinning, ShaderType::Fragment> {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc }
			{}

			void InitUniforms()
			{
				uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
				uView = m_rc->GetUniformLocation("uView");
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
				m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

				for (int i = 0; i != BaseState::MAX_LIGHTS; ++i)
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
					GetShaderFile(RenderContextType::LightPerFragmentDiffuseSkinning, ShaderType::Fragment), 1, names);
			}

			GLuint m_index{ 0 };
			GlRenderContextBase* m_rc;
			unsigned uDiffuseColor;
			unsigned uView;
			LightSourceShaderParameters uLight[BaseState::MAX_LIGHTS];
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_LIGHT_PER_FRAGMENT_DIFFUSE_SKINNING
