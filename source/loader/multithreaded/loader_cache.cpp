#include "loader_cache.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    LoaderCache::LoaderCache()
    {
    }

    LoaderCache* LoaderCache::Clone() const {
        return new LoaderCache(*this);
    }
}
PUNK_ENGINE_END
