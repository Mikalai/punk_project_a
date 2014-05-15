#include <core/ifactory.h>
#include "light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	void Light::QueryInterface(std::uint64_t type, void** object) {
		if (!object)
			return;

		if (type == typeid(IDirectionalLight).hash_code() ||
			type == typeid(IPointLight).hash_code() ||
			type == typeid(ISpotLight).hash_code() ||
			type == typeid(ILight).hash_code())
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

	PUNK_REGISTER_CREATOR(IDirectionalLight, CreateLight);
	PUNK_REGISTER_CREATOR(ISpotLight, CreateLight);
	PUNK_REGISTER_CREATOR(IPointLight, CreateLight);
	
}
PUNK_ENGINE_END
