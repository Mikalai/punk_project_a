#include "engine_objects.h"
#include "async_loader.h"

PUNK_ENGINE_BEGIN
namespace System
{
    AsyncLoader::AsyncLoader()
    {
    }

    AsyncLoader::~AsyncLoader()
    {
    }

	void AsyncLoader::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == IID_IAsyncLoader) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}
}
PUNK_ENGINE_END

