#include "engine_objects.h"
#include "async_loader.h"

PUNK_ENGINE_BEGIN
namespace System
{
    Core::Rtti AsyncLoader::Type{"System.AsyncLoader", typeid(AsyncLoader).hash_code(), {&Core::Object::Type}};

    AsyncLoader::AsyncLoader()
    {
    }

    AsyncLoader::~AsyncLoader()
    {
    }
}
PUNK_ENGINE_END

