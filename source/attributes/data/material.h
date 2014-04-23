#ifndef _H_PUNK_VIRTUAL_MATERIAL
#define _H_PUNK_VIRTUAL_MATERIAL

#include <iosfwd>
#include <map>

#include <config.h>
#include <core/object.h>
#include <math/vec4.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class TextureSlot;

    class PUNK_ENGINE_API Material : public Core::Object
	{
	public:		

		Material();
        Material(const Material&) = delete;
        Material& operator = (const Material&) = delete;
        virtual ~Material();

		void SetDiffuseMap(const Core::String& map);
		void SetNormalMap(const Core::String& map);
        void SetSpecularMap(const Core::String& map);
		void SetDiffuseColor(const Math::vec4& color);
		void SetSpecularColor(const Math::vec4& color);
		void SetSpecularFactor(float value);
		void SetName(const Core::String& name);

		const Core::String& GetDiffuseMap() const;
		const Core::String& GetNormalMap() const;
		const Math::vec4& GetDiffuseColor() const;
		const Math::vec4& GetSpecularColor() const;
		float GetSpecularFactor() const;
		const Core::String& GetName() const;

		void SetAlpha(float value) { m_diffuse_color[3] = value; }
		float GetAlpha() const { return m_diffuse_color[3]; }

		void SetAmbient(float value) { m_ambient = value; }
		float GetAmbient() const { return m_ambient; }

		void SetDiffuseIntensity(float value) { m_diffuse_intensity = value; }
		float GetDiffuseIntensity() const { return m_diffuse_intensity; }

		void SetDarkness(float value) { m_darkness = value; }
		float GetDarkness() const { return m_darkness; }

		void SetDiffuseFresnel(float value ) { m_diffuse_fresnel = value; }
		float GetDiffuseFresnel() const { return m_diffuse_fresnel; }

		void SetDiffuseFresnelFactor(float value) { m_diffuse_fresnel_factor = value; }
		float GetDiffuseFresnelFactor() const { return m_diffuse_fresnel_factor; }

		void SetEmit(float value) { m_emit = value; }
		float GetEmit() const { return m_emit; }

		void SetMirrorColor(Math::vec4 value) { m_mirror_color = value; }
		const Math::vec4 GetMirrorColor() const { return m_mirror_color; }

		void SetRoughness(float value) { m_roughness = value; }
		float GetRoughness() const { return m_roughness; }

		void SetSpecularAlpha(float value) { m_specular_color[3] = value; }
		float GetSpecularAlpha() const { return m_specular_color[3]; }

		void SetSpecularIntensity(float value) { m_specular_intensity = value; }
		float GetSpecularIntensity() const { return m_specular_intensity; }

		void SetSpecularIndexOfRefraction(float value) { m_specular_index_of_refraction = value; }
		float GetSpecularIndexOfRefraction() const { return m_specular_index_of_refraction; }

		void SetSpecularSlope(float value) { m_specular_slope = value; }
		float GetSpecularSlope() const { return m_specular_slope; }

		void SetTranslucency(float value) { m_translucency = value; }
		float GetTranslucency() const { return m_translucency; }

        void AddTextureSlot(TextureSlot* value);
        TextureSlot* GetTextureSlot(size_t index);
        const TextureSlot* GetTextureSlot(size_t index) const;
        size_t GetTextureSlotCount() const;		

		static Material* CreateFromFile(const Core::String& path);
		static Material* CreateFromStream(std::istream& stream);

	private:
		
		Core::String m_diffuse_map;
		Core::String m_normal_map;
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

        std::vector<TextureSlot*> m_texture_slots;

        PUNK_OBJECT(Material)
	};

	typedef std::map<Core::String, Material> Materials;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_MATERIAL