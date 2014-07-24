#include <memory>
#include <system/factory/module.h>
#include <string/module.h>
#include <core/iserializable.h>
#include "texture_slot.h"
#include <iosfwd>
#include <map>

#include <config.h>
#include <core/object.h>
#include <math/tuple.h>
#include <string/string.h>
#include "imaterial.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class TextureSlot;

	class PUNK_ENGINE_LOCAL Material : public IMaterial, public Core::ISerializable
	{
	public:

		Material()
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

		virtual ~Material()
		{}

		Material(const Material&) = delete;
		Material& operator = (const Material&) = delete;

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			if (!object)
				return;
			
			*object = nullptr;
			
			if (type == IID_IMaterial ||
				type == Core::IID_IObject) {
				*object = (void*)(IMaterial*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (void*)(Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t Release() {
			std::uint32_t v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		std::uint32_t AddRef() {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}


		//	IMaterial
		void SetDiffuseTextureSlot(Core::Pointer<IDiffuseTextureSlot> value) override { 
			m_diffuse_textue_slot = value; 
		}

		void SetNormalTextureSlot(Core::Pointer<INormalTextureSlot> value) override { 
			m_normal_texture_slot = value;
		}

		void SetSpecularTextureSlot(Core::Pointer<ISpecularIntensityTextureSlot> value) override {
			m_specular_texture_slot = value;
		}

		Core::Pointer<IDiffuseTextureSlot> GetDiffuseTextureSlot() override { 
			return m_diffuse_textue_slot; 
		}

		Core::Pointer<INormalTextureSlot> GetNormalTextureSlot() override { 
			return m_normal_texture_slot;
		}

		Core::Pointer<ISpecularIntensityTextureSlot> GetSpecularTextureSlot() override {
			return m_specular_texture_slot;
		}

		void Material::SetDiffuseColor(const Math::vec4& color)
		{
			m_diffuse_color = color;
		}

		void SetSpecularColor(const Math::vec4& color) {
			m_specular_color = color;
		}

		void SetSpecularFactor(float value) {
			m_specular_factor = value;
		}

		void SetName(const Core::String& name) {
			m_name = name;
		}

		const Math::vec4& GetDiffuseColor() const {
			return m_diffuse_color;
		}

		const Math::vec4& GetSpecularColor() const {
			return m_specular_color;
		}

		float GetSpecularFactor() const {
			return m_specular_factor;
		}

		const Core::String& GetName() const {
			return m_name;
		}

		void SetAlpha(float value) override { 
			m_diffuse_color[3] = value; 
		}

		float GetAlpha() const override {
			return m_diffuse_color[3]; 
		}

		void SetAmbient(float value) override { 
			m_ambient = value; 
		}
		
		float GetAmbient() const override {
			return m_ambient; 
		}

		void SetDiffuseIntensity(float value) { 
			m_diffuse_intensity = value; 
		}

		float GetDiffuseIntensity() const override { 
			return m_diffuse_intensity; 
		}

		void SetDarkness(float value) override { 
			m_darkness = value; 
		}

		float GetDarkness() const override { 
			return m_darkness; 
		}

		void SetDiffuseFresnel(float value) override { 
			m_diffuse_fresnel = value; 
		}

		float GetDiffuseFresnel() const override { 
			return m_diffuse_fresnel; 
		}

		void SetDiffuseFresnelFactor(float value) override { 
			m_diffuse_fresnel_factor = value; 
		}

		float GetDiffuseFresnelFactor() const override { 
			return m_diffuse_fresnel_factor; 
		}

		void SetEmit(float value) override { 
			m_emit = value; 
		}
		
		float GetEmit() const override { 
			return m_emit; 
		}

		void SetMirrorColor(Math::vec4 value) override { 
			m_mirror_color = value; 
		}

		const Math::vec4 GetMirrorColor() const override { 
			return m_mirror_color; 
		}

		void SetRoughness(float value) override { 
			m_roughness = value; 
		}

		float GetRoughness() const override { 
			return m_roughness; 
		}

		void SetSpecularAlpha(float value) override { 
			m_specular_color[3] = value; 
		}

		float GetSpecularAlpha() const override { 
			return m_specular_color[3]; 
		}

		void SetSpecularIntensity(float value) override { 
			m_specular_intensity = value; 
		}
		
		float GetSpecularIntensity() const override { 
			return m_specular_intensity; 
		}

		void SetSpecularIndexOfRefraction(float value) override { 
			m_specular_index_of_refraction = value; 
		}

		float GetSpecularIndexOfRefraction() const override { 
			return m_specular_index_of_refraction; 
		}

		void SetSpecularSlope(float value) override { 
			m_specular_slope = value; 
		}

		float GetSpecularSlope() const override { 
			return m_specular_slope; 
		}

		void SetTranslucency(float value) override { 
			m_translucency = value; 
		}

		float GetTranslucency() const override { 
			return m_translucency; 
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WriteBuffer(CLSID_Material.ToPointer(), sizeof(CLSID_Material));

			//	IMaterial
			buffer.WriteString(m_name);
			buffer.WritePod(m_diffuse_color);
			buffer.WritePod(m_specular_color);
			buffer.WritePod(m_mirror_color);
			buffer.WriteReal32(m_specular_factor);
			buffer.WriteReal32(m_ambient);
			buffer.WriteReal32(m_diffuse_intensity);
			buffer.WriteReal32(m_darkness);
			buffer.WriteReal32(m_diffuse_fresnel);
			buffer.WriteReal32(m_diffuse_fresnel_factor);
			buffer.WriteReal32(m_emit);
			buffer.WriteReal32(m_roughness);
			buffer.WriteReal32(m_specular_intensity);
			buffer.WriteReal32(m_specular_index_of_refraction);
			buffer.WriteReal32(m_specular_slope);
			buffer.WriteReal32(m_translucency);

			bool flag = m_diffuse_textue_slot.get() != nullptr;
			if (m_diffuse_textue_slot) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_diffuse_textue_slot, Core::IID_ISerializable);
				flag &= serializable.get() != nullptr;
				buffer.WriteBoolean(flag);
				if (flag & serializable)
					serializable->Serialize(buffer);
			} else 
				buffer.WriteBoolean(flag);
			
			flag = m_normal_texture_slot.get() != nullptr;
			if (m_normal_texture_slot) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_normal_texture_slot, Core::IID_ISerializable);
				flag &= serializable.get() != nullptr;
				buffer.WriteBoolean(flag);
				if (flag & serializable)
					serializable->Serialize(buffer);
			}
			else 
				buffer.WriteBoolean(flag);

			flag = m_specular_texture_slot.get() != nullptr;
			if (m_specular_texture_slot) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_specular_texture_slot, Core::IID_ISerializable);
				flag &= serializable.get() != nullptr;
				buffer.WriteBoolean(flag);
				if (flag & serializable)
					serializable->Serialize(buffer);
			}
			else
				buffer.WriteBoolean(flag);
		}

		void Deserialize(Core::Buffer& buffer) override {
			//	IMaterial
			m_name = buffer.ReadString();
			buffer.ReadPod(m_diffuse_color);
			buffer.ReadPod(m_specular_color);
			buffer.ReadPod(m_mirror_color);
			m_specular_factor = buffer.ReadReal32();
			m_ambient = buffer.ReadReal32();
			m_diffuse_intensity = buffer.ReadReal32();
			m_darkness = buffer.ReadReal32();
			m_diffuse_fresnel = buffer.ReadReal32();
			m_diffuse_fresnel_factor = buffer.ReadReal32();
			m_emit = buffer.ReadReal32();
			m_roughness = buffer.ReadReal32();
			m_specular_intensity = buffer.ReadReal32();
			m_specular_index_of_refraction = buffer.ReadReal32();
			m_specular_slope = buffer.ReadReal32();
			m_translucency = buffer.ReadReal32();

			bool flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (serializable)
					serializable->Deserialize(buffer);
				m_diffuse_textue_slot = Core::QueryInterfacePtr<IDiffuseTextureSlot>(serializable, IID_IDiffuseTextureSlot);
			}

			flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (serializable)
					serializable->Deserialize(buffer);
				m_normal_texture_slot = Core::QueryInterfacePtr<INormalTextureSlot>(serializable, IID_INormalTextureSlot);
			}

			flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (serializable)
					serializable->Deserialize(buffer);
				m_specular_texture_slot = Core::QueryInterfacePtr<ISpecularIntensityTextureSlot>(serializable, IID_ISpecularIntensityTextureSlot);
			}
		}

	private:
		
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_specular_color;
		float m_specular_factor;		
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
		Core::Pointer<IDiffuseTextureSlot> m_diffuse_textue_slot{ nullptr, Core::DestroyObject };
		Core::Pointer<INormalTextureSlot> m_normal_texture_slot{ nullptr, Core::DestroyObject };
		Core::Pointer<ISpecularIntensityTextureSlot> m_specular_texture_slot{ nullptr, Core::DestroyObject };		
	};

	typedef std::map<Core::String, Material> Materials;		

	PUNK_REGISTER_CREATOR(CLSID_Material, (System::CreateInstance<Material, IMaterial>));
}
PUNK_ENGINE_END
