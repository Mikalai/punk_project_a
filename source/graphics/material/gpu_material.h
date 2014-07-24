#ifndef _H_PUNK_GPU_MATERIAL
#define _H_PUNK_GPU_MATERIAL

#include <config.h>
#include <math/forward.h>
#include <math/tuple.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class Material
	{
	public:
		Math::vec4 m_diffuse_color{ 0.8f, 0.8f, 0.8f, 1.0f };
		Math::vec4 m_text_color{ 1, 1, 1, 1 };
		Math::vec4 m_no_diffuse_texture_color{ 1, 1, 1, 1 };
		Math::vec4 m_specular_color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Math::vec4 m_mirror_color{ 0.0f, 0.0f, 0.0f, 1.0f };
		Math::vec4 m_emit_color{ 1, 1, 1, 1 };
		float m_ambient_color;
		float m_specular_factor{ 128 };
		float m_diffuse_intensity{ 1.0f };
		float m_diffuse_fresnel{ 1.0f };
		float m_diffuse_fresnel_factor{ 0.0f };
		float m_emit{ 0.0f };
		float m_roughness{ 0.0f };
		float m_specular_intensity{ 128.0f };
		float m_specular_index_of_refraction{ 1.0f };
		float m_specular_slope{ 0.0f };
		float m_translucency{ 0.0f };
		float m_darkness{ 0.0f };
	};
}
PUNK_ENGINE_END

#endif	//	H_PUNK_GPU_MATERIAL
