#ifndef LIGHT_PARAMETERS_H
#define LIGHT_PARAMETERS_H

#include <cstddef>
#include <config.h>
#include <math/forward.h>
#include <math/matrix.h>
#include "light_model.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class LightParameters
	{
	public:

		void SetPosition(float x, float y, float z)
		{
			m_position.Set(x, y, z, 1);
		}

		void SetPosition(const Math::point3d& value)
		{
			m_position.Set(value[0], value[1], value[2], 1);
		}

		const Math::point4d& GetPosition() const
		{
			return m_position;
		}

		void SetDirection(float x, float y, float z)
		{
			m_direction.Set(x, y, z, 0);
		}

		void SetDirection(const Math::vec3& value)
		{
			m_direction.Set(value[0], value[1], value[2], 0);
		}

		const Math::vec4& GetDirection() const
		{
			return m_direction;
		}

		void SetDiffuseColor(float r, float g, float b, float a)
		{
			m_diffuse_color.Set(r, g, b, a);
		}

		void SetDiffuseColor(const Math::vec4& value)
		{
			m_diffuse_color = value;
		}

		const Math::vec4& GetDiffuseColor() const
		{
			return m_diffuse_color;
		}

		void SetAmbientColor(float r, float g, float b, float a)
		{
			m_ambient_color.Set(r, g, b, a);
		}

		void SetAmbientColor(const Math::vec4& value)
		{
			m_ambient_color = value;
		}

		const Math::vec4& GetAmbientColor() const
		{
			return m_ambient_color;
		}

		void SetLightAttenuation(LightAttenuation value)
		{
			m_attenuation = value;
		}

		LightAttenuation GetLightAttenuation() const
		{
			return m_attenuation;
		}

		void SetLightConstantAttenuation(float value)
		{
			m_constant_attenuation = value;
		}

		float GetLightConstantAttenuation() const
		{
			return m_constant_attenuation;
		}

		void SetLightLinearAttenuation(float value)
		{
			m_linear_attenuation = value;
		}

		float GetLightLinearAttenuation() const
		{
			return m_linear_attenuation;
		}

		void SetLightQuadricAttenuation(float value)
		{
			m_quadric_attenuation = value;
		}

		float GetLightQuadricAttenuation() const
		{
			return m_quadric_attenuation;
		}

		void SetType(LightType value)
		{
			m_light_type = value;
		}

		LightType GetType() const
		{
			return m_light_type;
		}

		void SetSpotExponent(float value)
		{
			m_spot_exponent = value;
		}

		float GetSpotExponent() const
		{
			return m_spot_exponent;
		}

		const Math::mat4 GetProjectionMatrix() const
		{
			if (m_light_type == LightType::Spot)
			{
				Math::mat4 res = Math::mat4::CreatePerspectiveProjection(m_spot_exponent, 1, 1, 0.1, 100.0);
				return res;
			}
			else
			{
				Math::mat4 res = Math::mat4::CreateOrthographicProjection2(-16, 16, -16, 16, 0.1, 100.0);
				return res;
			}
		}

		const Math::mat4 GetViewMatrix() const
		{
			Math::mat4 res = Math::mat4::CreateViewMatrix(m_position.XYZ(), (m_position + m_direction).XYZ(), Math::vec3(0, 0, 1));
			return res;
		}

		void SetShadowMatrix(size_t index, const Math::mat4& value)
		{
			m_shadow_matrix[index] = value;
		}

		const Math::mat4& GetShadowMatrix(size_t index) const
		{
			return m_shadow_matrix[index];
		}

		void SetFarDistance(size_t index, float value)
		{
			m_far_distance[index] = value;
		}

		float GetFarDistance(size_t index) const
		{
			return m_far_distance[index];
		}

		const Math::vec4& GetFarDistances() const
		{
			return m_far_distance;
		}

		void SetFarZ(float value)
		{
			m_zfar = value;
		}

		float GetFarZ() const
		{
			return m_zfar;
		}

		void SetNearZ(float value)
		{
			m_znear = value;
		}

		float GetNearZ() const
		{
			return m_znear;
		}

		void SetEnable(bool value)
		{
			m_enabled = value;
		}

		bool IsEnabled() const
		{
			return m_enabled;
		}

		void Enable()
		{
			m_enabled = true;
		}

		void Disable()
		{
			m_enabled = false;
		}

		void SetSpecularColor(const Math::vec4& value)
		{
			m_specular_color = value;
		}

		void SetSpecularColor(float r, float g, float b, float a)
		{
			m_specular_color.Set(r, g, b, a);
		}

		const Math::vec4& GetSpecularColor() const
		{
			return m_specular_color;
		}

		void SetViewDirection(const Math::vec3& value)
		{
			m_view_direction = value;
		}

		const Math::vec4& GetViewDirection() const
		{
			return m_view_direction;
		}

		void SetViewPosition(const Math::point4d& value)
		{
			m_view_position = value;
		}

		const Math::point4d& GetViewPosition() const
		{
			return m_view_position;
		}

	private:
		LightType m_light_type{ LightType::Direction };
		LightAttenuation m_attenuation{ LightAttenuation::Constant };
		float m_constant_attenuation{ 1 };
		float m_linear_attenuation{ 0 };
		float m_quadric_attenuation{ 0 };
		float m_spot_exponent{ 100.0f };
        /// World light position
		Math::point4d m_position;
        /// World light direction
		Math::vec4 m_direction{ 1, 0, 0, 0 };
        Math::point4d m_view_position;
        Math::vec4 m_view_direction;
		Math::vec4 m_diffuse_color{ 1, 1, 1, 1 };
		Math::vec4 m_ambient_color;
        Math::mat4 m_shadow_matrix[4];
        Math::vec4 m_far_distance;
		Math::vec4 m_specular_color{ 1, 1, 1, 1 };
		float m_zfar{ 1 };
		float m_znear{ 0 };
		bool m_enabled{ false };
	};
}
PUNK_ENGINE_END

#endif // LIGHT_PARAMETERS_H
