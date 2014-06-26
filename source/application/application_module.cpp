#include <system/module.h>
#include <system/factory/module.h>
#include "module.h"

PUNK_ENGINE_BEGIN
namespace Runtime {

    System::ThreadMutex g_module_lock;
    System::IModule* g_module;

    class PUNK_ENGINE_LOCAL ApplicationModule : public System::IModule {
    public:
        ApplicationModule()
            : m_ref_count{ 0 }
        {
            Init();
        }

        virtual ~ApplicationModule() {
            Clear();
        }

        //  IObject
        void QueryInterface(const Core::Guid& type, void** object) {
            Core::QueryInterface(this, type, object, { Core::IID_IObject, System::IID_IModule});
        }

        std::uint32_t AddRef() {
            return m_ref_count.fetch_add(1);
        }

        std::uint32_t Release() {
            auto v = m_ref_count.fetch_sub(1) - 1;
            if (!v)
                delete this;
            return v;
        }

    private:
        void Init() {
        }

        void Clear() {
        }

    private:
        std::atomic<std::uint32_t> m_ref_count{ 0 };
    };

    extern "C" PUNK_ENGINE_API System::IModule* GetPunkModule() {
        System::ThreadMutexLock lock(g_module_lock);
        if (!g_module)
            g_module = new ApplicationModule();
        return g_module;
    }
}
PUNK_ENGINE_END

