#include <core/ifactory.h>
#include <cstdint>
#include "idirectional_light.h"
#include "ispot_light.h"
#include "ipoint_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Light : public IDirectionalLight, public IPointLight, public ISpotLight {
	public:
		Light();
		virtual ~Light();

		///	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ILight
		void SetEnergy(float value) override { m_energy = value; }
		float GetEnergy() const override { return m_energy; }
		void SetDiffuseColor(const Math::vec3& value) override { m_diffuse_color = value; }
		const Math::vec3& GetDiffuseColor() const override { return m_diffuse_color; }
		void SetSpecularColor(const Math::vec3& value) override { m_specular_color = value; }
		const Math::vec3& GetSpecularColor() const override { return m_specular_color; }
		void SetName(const Core::String& value) override { m_name = value; }
		const Core::String GetName() const override { return m_name; }

		//	IDirectionalLight
		const Math::vec3 GetDirection() const override { return m_direction; }
		void SetDirection(const Math::vec3& value) override { m_direction = value; }

		//	IPointLight
		void SetDistance(float value) override { m_distance = value; }
		float GetDistance() const { return m_distance; }
		void SetLinearAttenuation(float value) { m_linear_attenuation = value; }
		float GetLinearAttenuation() const { return m_linear_attenuation; }
		void SetQuadraticAttenuation(float value) { m_quadratic_attenuation = value; }
		float GetQuadraticAttenuation() const { return m_quadratic_attenuation; }

	private:
		//	ilight
		Math::vec3 m_diffuse_color;
		Math::vec3 m_specular_color;
		float m_energy;
		Core::String m_name;

		//	idirectionallight
		Math::vec3 m_direction{ 0, 0, -1 };

		//	ipointlight
		float m_distance;
		float m_linear_attenuation;
		float m_quadratic_attenuation;

		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};


	Light::Light() {}

	Light::~Light() {}

	void Light::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == IID_IDirectionalLight) {
			*object = (IDirectionalLight*)this;
			AddRef();
		}
		else if (type == IID_IPointLight) {
			*object = (IPointLight*)this;
			AddRef();
		}
		else if (type == IID_ISpotLight) {
			*object = (ISpotLight*)this;
			AddRef();
		}
		else if (type == IID_ILight) {		
			*object = (ILight*)(IPointLight*)this;
			AddRef();
		}
		else {
			*object = nullptr;
		}
	}

	std::uint32_t Light::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t Light::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}
	
	void CreateDirectionalLight(void** object) {
		if (!object)
			return;
		*object = (IDirectionalLight*)(new Light);
	}

	void CreatePointLight(void** object) {
		if (!object)
			return;
		*object = (IPointLight*)(new Light);
	}

	void CreateSpotLight(void** object) {
		if (!object)
			return;
		*object = (ISpotLight*)(new Light);
	}


	PUNK_REGISTER_CREATOR(IID_IDirectionalLight, CreateDirectionalLight);
	PUNK_REGISTER_CREATOR(IID_ISpotLight, CreateSpotLight);
	PUNK_REGISTER_CREATOR(IID_IPointLight, CreatePointLight);
	
}
PUNK_ENGINE_END
