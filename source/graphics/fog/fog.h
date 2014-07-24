#ifndef FOG_H
#define FOG_H

#include <math/forward.h>
#include <math/tuple.h>
#include "fog_mode.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class FogDescription
	{
	public:

		void Enable(bool value)
		{
			m_enable = value;
		}

		void SetMode(FogMode value)
		{
			m_mode = value;
		}

		void SetColor(const Math::vec4& value)
		{
			m_color = value;
		}

		void SetColor(float r, float g, float b, float a)
		{
			m_color.Set(r, g, b, a);
		}

		void SetDensity(float value)
		{
			m_density = value;
		}

		void SetStart(float value)
		{
			m_start = value;
		}

		void SetEnd(float value)
		{
			m_end = value;
		}

		bool IsEnabled() const
		{
			return m_enable;
		}

		FogMode GetMode() const
		{
			return m_mode;
		}

		const Math::vec4& GetColor() const
		{
			return m_color;
		}

		float GetDensity() const
		{
			return m_density;
		}

		float GetStart() const
		{
			return m_start;
		}

		float GetEnd() const
		{
			return m_end;
		}

		void SetScale(float value)
		{
			m_scale = value;
		}

		float GetScale() const
		{
			return m_scale;
		}

	private:
		bool m_enable{ false };
		FogMode m_mode{ FogMode::Linear };
		Math::vec4 m_color{ 1, 1, 1, 1 };
		float m_density{ 1 };
		float m_start{ 0 };
		float m_end{ 1 };
		float m_scale{ 1 };
	};
}
PUNK_ENGINE_END

#endif // FOG_H
