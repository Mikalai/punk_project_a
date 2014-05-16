#include <memory>
#include <istream>
#include <ostream>
#include <string/module.h>
#include "texture_slot.h"
#include "material.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{

	void CreateMaterial(void** object) {
		if (!object)
			return;
		*object = (void*)(new Material);
	}

    Material::Material()
		: m_diffuse_color(0.1f, 0.1f, 0.1f, 1.0f)
		, m_specular_color(1.0f, 1.0f, 1.0f, 1.0f)
		, m_specular_factor(128)
		, m_name(L"")
		, m_ambient(0.0f)
		, m_diffuse_intensity(1.0f)
		, m_darkness(0.0f)
		, m_diffuse_fresnel(1.0f)
		, m_diffuse_fresnel_factor(0.0f)
		, m_emit(0.0f)
		, m_mirror_color(0.0f, 0.0f, 0.0f, 1.0f)
		, m_roughness(0.0f)
		, m_specular_intensity(128.0f)
		, m_specular_index_of_refraction(1.0f)
		, m_specular_slope(0.0f)
		, m_translucency(0.0f)
    {}

	void Material::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == IID_IMaterial ||
			type == Core::IID_IObject) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

//	Material::Material(const Utility::MaterialDesc& desc)
//	{
//		m_diffuse_map = desc.m_diffuse_map;
//		m_normal_map = desc.m_normal_map;
//		m_diffuse_color = desc.m_diffuse_color; m_diffuse_color.W() = desc.m_alpha;
//		m_specular_color = desc.m_specular_color; m_specular_color.W() = desc.m_specular_alpha;
//		m_specular_factor = desc.m_specular_factor;
//		m_name = desc.m_name;
//		m_ambient = desc.m_ambient;
//		m_diffuse_intensity = desc.m_diffuse_intensity;
//		m_darkness = desc.m_darkness;
//		m_diffuse_fresnel = desc.m_diffuse_fresnel;
//		m_diffuse_fresnel_factor = desc.m_diffuse_fresnel_factor;
//		m_emit = desc.m_emit;
//		m_mirror_color = desc.m_mirror_color;
//		m_roughness = desc.m_roughness;
//		m_specular_intensity = desc.m_specular_intensity;
//		m_specular_index_of_refraction = desc.m_specular_index_of_refraction;
//		m_specular_slope = desc.m_specular_slope;
//		m_translucency = desc.m_translucency;
//	}

    Material::~Material()
    {
		if (m_diffuse_textue_slot)
			m_diffuse_textue_slot->Release();
		if (m_normal_texture_slot)
			m_normal_texture_slot->Release();
		if (m_specular_texture_slot)
			m_specular_texture_slot->Release();
    }

	void Material::SetDiffuseColor(const Math::vec4& color)
	{
		m_diffuse_color = color;
	}

	void Material::SetSpecularColor(const Math::vec4& color)
	{
		m_specular_color = color;
	}

	void Material::SetSpecularFactor(float value)
	{
		m_specular_factor = value;
	}

	void Material::SetName(const Core::String& name)
	{
		m_name = name;
	}

	const Math::vec4& Material::GetDiffuseColor() const
	{
		return m_diffuse_color;
	}

	const Math::vec4& Material::GetSpecularColor() const
	{
		return m_specular_color;
	}

	float Material::GetSpecularFactor() const
	{
		return m_specular_factor;
	}

	const Core::String& Material::GetName() const
	{
		return m_name;
	}
}
PUNK_ENGINE_END
