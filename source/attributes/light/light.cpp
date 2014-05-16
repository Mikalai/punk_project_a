#include <core/ifactory.h>
#include "light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	Light::Light() {}

	Light::~Light() {}

	void Light::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == IID_IDirectionalLight ||
			type == IID_IPointLight ||
			type == IID_ISpotLight ||
			type == IID_ILight)
		{
			*object = (void*)this;
			AddRef();
		}
		else {
			*object = nullptr;
		}
	}

	void CreateLight(void** object) {
		if (!object)
			return;
		*object = (void*)( new Light );
	}

	PUNK_REGISTER_CREATOR(IID_IDirectionalLight, CreateLight);
	PUNK_REGISTER_CREATOR(IID_ISpotLight, CreateLight);
	PUNK_REGISTER_CREATOR(IID_IPointLight, CreateLight);
	
}
PUNK_ENGINE_END
