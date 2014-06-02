#ifndef _H_PUNK_VIRTUAL_MATERIAL
#define _H_PUNK_VIRTUAL_MATERIAL

#include <iosfwd>
#include <map>

#include <config.h>
#include <core/object.h>
#include <math/vec4.h>
#include <string/string.h>
#include "imaterial.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class TextureSlot;

    class PUNK_ENGINE_LOCAL Material : public IMaterial
	{
	public:		

		Material();
        Material(const Material&) = delete;
        Material& operator = (const Material&) = delete;
        virtual ~Material();
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IMaterial
		void SetDiffuseTextureSlot(IDiffuseTextureSlot* value) override { m_diffuse_textue_slot = value; }
		void SetNormalTextureSlot(INormalTextureSlot* value) override { m_normal_texture_slot = value; }
		void SetSpecularTextureSlot(ISpecularIntensityTextureSlot* value) override { m_specular_texture_slot = value; }
		IDiffuseTextureSlot* GetDiffuseTextureSlot() override { return m_diffuse_textue_slot; }
		INormalTextureSlot* GetNormalTextureSlot() override { return m_normal_texture_slot; }
		ISpecularIntensityTextureSlot* GetSpecularTextureSlot() override { return m_specular_texture_slot; }

		void SetDiffuseColor(const Math::vec4& color) override;
		void SetSpecularColor(const Math::vec4& color) override;
		void SetSpecularFactor(float value) override;
		void SetName(const Core::String& name) override;
		const Math::vec4& GetDiffuseColor() const override;
		const Math::vec4& GetSpecularColor() const override;
		float GetSpecularFactor() const override;
		const Core::String& GetName() const override;

		void SetAlpha(float value) override { m_diffuse_color[3] = value; }
		float GetAlpha() const override{ return m_diffuse_color[3]; }

		void SetAmbient(float value) override { m_ambient = value; }
		float GetAmbient() const override{ return m_ambient; }

		void SetDiffuseIntensity(float value) { m_diffuse_intensity = value; }
		float GetDiffuseIntensity() const override { return m_diffuse_intensity; }

		void SetDarkness(float value) override { m_darkness = value; }
		float GetDarkness() const override { return m_darkness; }

		void SetDiffuseFresnel(float value) override { m_diffuse_fresnel = value; }
		float GetDiffuseFresnel() const override { return m_diffuse_fresnel; }

		void SetDiffuseFresnelFactor(float value) override { m_diffuse_fresnel_factor = value; }
		float GetDiffuseFresnelFactor() const override { return m_diffuse_fresnel_factor; }

		void SetEmit(float value) override { m_emit = value; }
		float GetEmit() const override { return m_emit; }

		void SetMirrorColor(Math::vec4 value) override { m_mirror_color = value; }
		const Math::vec4 GetMirrorColor() const override { return m_mirror_color; }

		void SetRoughness(float value) override { m_roughness = value; }
		float GetRoughness() const override { return m_roughness; }

		void SetSpecularAlpha(float value) override { m_specular_color[3] = value; }
		float GetSpecularAlpha() const override { return m_specular_color[3]; }

		void SetSpecularIntensity(float value) override { m_specular_intensity = value; }
		float GetSpecularIntensity() const override { return m_specular_intensity; }

		void SetSpecularIndexOfRefraction(float value) override { m_specular_index_of_refraction = value; }
		float GetSpecularIndexOfRefraction() const override { return m_specular_index_of_refraction; }

		void SetSpecularSlope(float value) override { m_specular_slope = value; }
		float GetSpecularSlope() const override { return m_specular_slope; }

		void SetTranslucency(float value) override { m_translucency = value; }
		float GetTranslucency() const override { return m_translucency; }		

	private:
		
		IDiffuseTextureSlot* m_diffuse_textue_slot{ nullptr };
		INormalTextureSlot* m_normal_texture_slot{ nullptr };
		ISpecularIntensityTextureSlot* m_specular_texture_slot{ nullptr };
        Core::String m_specular_map;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_specular_color;
		float m_specular_factor;
		Core::String m_name;
		float m_ambient;
		float m_diffuse_intensity;
		float m_darkness;
		float m_diffuse_fresnel;
		float m_diffuse_fresnel_factor;
		float m_emit;
		Math::vec4 m_mirror_color;
		float m_roughness;
		float m_specular_intensity;
		float m_specular_index_of_refraction;
		float m_specular_slope;
		float m_translucency;				
		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};

	typedef std::map<Core::String, Material> Materials;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_MATERIAL
