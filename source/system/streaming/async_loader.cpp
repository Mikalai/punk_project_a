#include "engine_objects.h"
#include "async_loader.h"

PUNK_ENGINE_BEGIN
namespace System
{
    AsyncLoader::AsyncLoader()
		: m_container{ this, Core::GetRootObject() }
    {
    }

    AsyncLoader::~AsyncLoader()
    {
    }

	void AsyncLoader::QueryInterface(std::uint64_t type, void** object) {
		if (!object)
			return;

		if (type == typeid(Core::IObject).hash_code() ||
			type == typeid(IAsyncLoader).hash_code()) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}
}
PUNK_ENGINE_END

