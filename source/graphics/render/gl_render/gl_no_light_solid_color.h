#ifndef _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D
#define _H_PUNK_OPENGL_VERTEX_SHADER_SOLID_3D

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
		struct ShaderAspect < RenderContextType::NoLightSolidColor, ShaderType::Vertex > {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc } {}

			void InitUniforms()
			{
				uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
			}

			void BindParameters(const CoreState& params)
			{
				auto proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
				m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
			}

			int64_t GetRequiredAttributesSet() const
			{
				return VertexComponent::Position::Value();
			}

			GLuint GetIndex() {
				return m_index;
			}

			void Cook() {
				System::Folder f;
				f.Open(System::Environment::Instance()->GetShaderFolder());				
				m_index = ShaderCooker::CookFromFile(ShaderType::Vertex, 
					GetShaderFile(RenderContextType::NoLightSolidColor, ShaderType::Vertex));
			}

			GLuint m_index;
			GlRenderContextBase* m_rc;
			unsigned uProjViewWorld;
		};

		template<>
		struct ShaderAspect<RenderContextType::NoLightSolidColor, ShaderType::Fragment> {

			ShaderAspect(GlRenderContextBase* rc)
				: m_rc{ rc }
			{}

			void InitUniforms()
			{
				uDiffuseColor = m_rc->GetUniformLocation("uDiffuseColor");
			}

			void BindParameters(const CoreState& params)
			{
				//  GL_CALL(glPolygonOffset(1.0f, 4096.0f));
				m_rc->SetUniformVector4f(uDiffuseColor, &params.batch_state->m_material.m_diffuse_color[0]);
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
				m_index = ShaderCooker::CookFromFile(ShaderType::Fragment, 
					GetShaderFile(RenderContextType::NoLightSolidColor, ShaderType::Fragment));
			}

			GLuint m_index{ 0 };
			GlRenderContextBase* m_rc;
			unsigned uDiffuseColor;
		};
	}
}
PUNK_ENGINE_END

#endif
