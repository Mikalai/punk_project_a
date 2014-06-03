#include <sstream>
#include "vs_per_vertex_lighting_diffuse.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		VsPerVertexLightingDiffuse::VsPerVertexLightingDiffuse()
			: Shader(ShaderType::Vertex)
		{
			CookFromFile(System::Environment::Instance()->GetShaderFolder()
				+ GetShaderFile(ShaderCollection::VertexLightPerVertexDiffuse));
		}

		void VsPerVertexLightingDiffuse::InitUniforms()
		{
			uProjViewWorld = m_rc->GetUniformLocation("uProjViewWorld");
			uNormalMatrix = m_rc->GetUniformLocation("uNormalMatrix");
			uViewWorld = m_rc->GetUniformLocation("uViewWorld");
			uView = m_rc->GetUniformLocation("uView");

			for (int i = 0; i != BaseState::MAX_LIGHTS; ++i)
			{
				{
					std::stringstream stream;
					stream << "uLight[" << i << "].ambient_color";
					uLight[i].ambient_color = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].attenuation_constant";
					uLight[i].attenuation_constant = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].attenuation_linear";
					uLight[i].attenuation_linear = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].attenuation_model";
					uLight[i].attenuation_model = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].attenuation_quadric";
					uLight[i].attenuation_quadric = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].diffuse_color";
					uLight[i].diffuse_color = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].direction";
					uLight[i].direction = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].position";
					uLight[i].position = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].spot";
					uLight[i].spot = m_rc->GetUniformLocation(stream.str().c_str());
				}

				{
					std::stringstream stream;
					stream << "uLight[" << i << "].type";
					uLight[i].type = m_rc->GetUniformLocation(stream.str().c_str());
				}
			}
		}

		void VsPerVertexLightingDiffuse::BindParameters(const CoreState& params)
		{
			const Math::mat4 proj_view_world = params.view_state->m_projection * params.view_state->m_view * params.batch_state->m_world;
			const Math::mat3 normal_matrix = (params.view_state->m_view * params.batch_state->m_world).RotationPart().Transposed().Inversed();
			const Math::mat4 view_world = params.view_state->m_view * params.batch_state->m_world;
			m_rc->SetUniformMatrix4f(uProjViewWorld, proj_view_world);
			m_rc->SetUniformMatrix3f(uNormalMatrix, normal_matrix);
			m_rc->SetUniformMatrix4f(uViewWorld, view_world);
			m_rc->SetUniformMatrix4f(uView, params.view_state->m_view);

			for (int i = 0; i != BaseState::MAX_LIGHTS; ++i)
			{
				m_rc->SetUniformInt(uLight[i].enabled, params.light_state->m_lights[i].IsEnabled());
				m_rc->SetUniformVector4f(uLight[i].position, params.light_state->m_lights[i].GetPosition());
				m_rc->SetUniformVector4f(uLight[i].diffuse_color, params.light_state->m_lights[i].GetDiffuseColor());
				m_rc->SetUniformVector4f(uLight[i].direction, params.light_state->m_lights[i].GetDirection());
				m_rc->SetUniformFloat(uLight[i].attenuation_constant, params.light_state->m_lights[i].GetLightConstantAttenuation());
				m_rc->SetUniformFloat(uLight[i].attenuation_linear, params.light_state->m_lights[i].GetLightLinearAttenuation());
				m_rc->SetUniformFloat(uLight[i].attenuation_quadric, params.light_state->m_lights[i].GetLightQuadricAttenuation());
				m_rc->SetUniformFloat(uLight[i].spot, params.light_state->m_lights[i].GetSpotExponent());

				switch (params.light_state->m_lights[i].GetLightAttenuation())
				{
				case LightAttenuation::Constant:
					m_rc->SetUniformInt(uLight[i].attenuation_model, 0);
					break;
				case LightAttenuation::Linear:
					m_rc->SetUniformInt(uLight[i].attenuation_model, 1);
					break;
				case LightAttenuation::Quadratic:
					m_rc->SetUniformInt(uLight[i].attenuation_model, 2);
					break;
				}

				switch (params.light_state->m_lights[i].GetType())
				{
				case LightType::Point:
					m_rc->SetUniformInt(uLight[i].type, 0);
					break;
				case LightType::Direction:
					m_rc->SetUniformInt(uLight[i].type, 1);
				case LightType::Spot:
					m_rc->SetUniformInt(uLight[i].type, 2);
					break;
				}
			}
		}

		int64_t VsPerVertexLightingDiffuse::GetRequiredAttributesSet() const
		{
			return VertexComponent::Position::Value() | VertexComponent::Normal::Value();
		}
	}
}
PUNK_ENGINE_END
