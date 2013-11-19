#include "engine_objects.h"
#include "async_loader.h"

namespace System
{
    PUNK_OBJECT_REG(AsyncLoader, "System.AsyncLoader", PUNK_ASYNC_LOADER, nullptr, nullptr, &Object::Info.Type);

    AsyncLoader::AsyncLoader()
    {
        Info.Add(this);
    }

    AsyncLoader::~AsyncLoader()
    {
        Info.Remove(this);
    }
}
