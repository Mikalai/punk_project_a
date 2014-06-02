#include <core/ifactory.h>
#include "light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

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
