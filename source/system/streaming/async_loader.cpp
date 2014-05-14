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
}
PUNK_ENGINE_END

