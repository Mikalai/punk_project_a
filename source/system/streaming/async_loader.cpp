#include "engine_objects.h"
#include "async_loader.h"

PUNK_ENGINE_BEGIN
namespace System
{
	Core::Rtti AsyncLoaderType{ "System.AsyncLoader", typeid(AsyncLoader).hash_code(), { Core::Object::Type() } };

	Core::Rtti* AsyncLoader::Type() {
		return &AsyncLoaderType;
	}

    AsyncLoader::AsyncLoader()
    {
    }

    AsyncLoader::~AsyncLoader()
    {
    }
}
PUNK_ENGINE_END

