#ifndef LOADER_CACHE_H
#define LOADER_CACHE_H

#include <config.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Scene {
    class INode;
}

namespace Loader {
    class LoaderCache
    {
    public:
        LoaderCache();
        LoaderCache* Clone() const;
        AsyncParserTask* m_task {nullptr};
        Scene::INode* m_parent {nullptr};
        bool m_delete{nullptr};
    };
}
PUNK_ENGINE_END


#endif // LOADER_CACHE_H
