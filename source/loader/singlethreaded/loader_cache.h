#ifndef LOADER_CACHE_H
#define LOADER_CACHE_H

#include <config.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {
    class INode;
}

namespace IoModule {
    class LoaderCache
    {
    public:
        LoaderCache();
        LoaderCache* Clone() const;
        AsyncParserTask* m_task {nullptr};
		Core::Pointer<SceneModule::INode> m_parent{ nullptr, Core::DestroyObject };
        bool m_delete{nullptr};
    };
}
PUNK_ENGINE_END


#endif // LOADER_CACHE_H
