#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string/module.h>
#include "pool_manager.h"
#include "pool.h"

PUNK_ENGINE_BEGIN
namespace Core {

    Pool::Pool() {}

#ifdef _DEBUG
    Pool::Pool(const String &name)
        : m_name(name) {
        auto buffer = m_name.ToWchar();
        wchar_t* type = (wchar_t*)buffer.Data();
        std::wcout << "Create pool for " << type << std::endl;
    }
#endif

#ifdef _NDEBUG
    Pool::~Pool() {
        Clear();
    }
#endif

    void* Pool::Alloc(size_t size) {
        if (m_free.empty()) {
#ifdef _DEBUG
            auto buffer = m_name.ToWchar();
            wchar_t* type = (wchar_t*)buffer.Data();
            std::wcout << "Allocation requested for " << type << " " << size << " bytes" << std::endl;
#endif
            void* result = malloc(size);
            memset(result, 0, size);
            return result;
        }
        void* result = m_free.front();
        memset(result, 0, size);
        m_free.pop_front();
        return result;
    }

    void Pool::Free(void* value) {
        m_free.push_back(value);
    }

    void Pool::Clear() {
#ifdef _DEBUG
        auto buffer = m_name.ToWchar();
        wchar_t* type = (wchar_t*)buffer.Data();
        std::wcout << L"Clear pool " << type << std::endl;
#else
       std::cout << "Clear pool" << std::endl;
#endif
        for (typename std::deque<void*>::iterator it = m_free.begin(); it != m_free.end(); ++it) {
            free(*it);
        }
        m_free.clear();
    }
}
PUNK_ENGINE_END
