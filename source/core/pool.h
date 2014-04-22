#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include <stddef.h>
#include <deque>
#include <config.h>

#ifdef _DEBUG
#include <String/String.h>
#endif

PUNK_ENGINE_BEGIN
namespace Core {
    class PUNK_ENGINE_API Pool {
    public:
        Pool();
#ifdef _DEBUG
        Pool(const Core::String& name);
#endif
        ~Pool();
        void* Alloc(size_t size);
        void Free(void* value);
        void Clear();
    private:
        std::deque<void*> m_free;
#ifdef _DEBUG
        Core::String m_name;
#endif
    };
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_POOL
