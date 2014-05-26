#include <map>
#include <system/logger/module.h>
#include <string/module.h>
#include <core/iobject.h>
#include "serializer.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

    std::map<std::int64_t, void (*)(Core::Buffer*, const Core::IObject*)> g_savers;
    std::map<std::int64_t, void (*)(Core::Buffer*, Core::IObject*)> g_loader;

    void RegisterSerializerFunction(std::int64_t type, void (*save)(Core::Buffer*, const Core::IObject*), void (*load)(Core::Buffer*, Core::IObject*)) {
        g_savers[type] = save;
        g_loader[type] = load;
    }

    void (*GetSaver(std::int64_t type))(Core::Buffer*, const Core::IObject*) {
        auto res = g_savers[type];
        if (res == nullptr)
            System::GetDefaultLogger()->Error(Core::String(L"No saver for type {0}").arg(type));
        return res;
    }

    void (*GetLoader(std::int64_t type))(Core::Buffer*, Core::IObject*) {
        auto res = g_loader[type];
        if (res == nullptr)
            System::GetDefaultLogger()->Error(Core::String(L"No loader for type {0}").arg(type));
        return res;
    }
}
PUNK_ENGINE_END
