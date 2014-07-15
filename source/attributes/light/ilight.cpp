#include <system/factory/module.h>
#include <string/module.h>
#include <core/iserializable.h>
#include <cstdint>
#include "idirectional_light.h"
#include "ispot_light.h"
#include "ipoint_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Light : 
		public IDirectionalLight, 
		public IPointLight, 
		public ISpotLight,
		public Core::ISerializable
	{
	public:

		Light() {}

		~Light() {}

		///	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			
			*object = nullptr;
			
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
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	ILight
		void SetEnergy(float value) override { 
			m_energy = value; 
		}
		
		float GetEnergy() const override { 
			return m_energy; 
		}
		
		void SetDiffuseColor(const Math::vec3& value) override { 
			m_diffuse_color = value; 
		}
		
		const Math::vec3& GetDiffuseColor() const override { 
			return m_diffuse_color; 
		}
		
		void SetSpecularColor(const Math::vec3& value) override { 
			m_specular_color = value; 
		}
		
		const Math::vec3& GetSpecularColor() const override { 
			return m_specular_color; 
		}
		
		void SetName(const Core::String& value) override { 
			m_name = value; 
		}
		
		const Core::String GetName() const override { 
			return m_name; 
		}

		//	IDirectionalLight
		const Math::vec3 GetDirection() const override { 
			return m_direction; 
		}
		
		void SetDirection(const Math::vec3& value) override { 
			m_direction = value; 
		}

		//	IPointLight
		void SetDistance(float value) override { 
			m_distance = value; 
		}
		
		float GetDistance() const override {
			return m_distance; 
		}
		
		void SetLinearAttenuation(float value) override {
			m_linear_attenuation = value; 
		}

		float GetLinearAttenuation() const override { 
			return m_linear_attenuation; 
		}
		
		void SetQuadraticAttenuation(float value) override {
			m_quadratic_attenuation = value; 
		}
		
		float GetQuadraticAttenuation() const override { 
			return m_quadratic_attenuation; 
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WritePod(CLSID_Light);

			//	ilight
			buffer.WritePod(m_diffuse_color);
			buffer.WritePod(m_specular_color);
			buffer.WriteReal32(m_energy);
			buffer.WriteString(m_name);

			//	idirectionallight
			buffer.WritePod(m_direction);

			//	ipointlight
			buffer.WriteReal32(m_distance);
			buffer.WriteReal32(m_linear_attenuation);
			buffer.WriteReal32(m_quadratic_attenuation);
		}
		
		void Deserialize(Core::Buffer& buffer) override {
			//	ilight
			buffer.ReadPod(m_diffuse_color);
			buffer.ReadPod(m_specular_color);
			m_energy = buffer.ReadReal32();
			buffer.WriteString(m_name);

			//	idirectionallight
			buffer.ReadPod(m_direction);

			//	ipointlight
			m_distance = buffer.ReadReal32();
			m_linear_attenuation = buffer.ReadReal32();
			m_quadratic_attenuation = buffer.ReadReal32();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };

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
		
	};	

	PUNK_REGISTER_CREATOR(CLSID_Light, (System::CreateInstance<Light, IDirectionalLight>));
	
}
PUNK_ENGINE_END
