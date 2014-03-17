#ifndef _H_PUNK_SYSTEM_POOLABLE
#define _H_PUNK_SYSTEM_POOLABLE

#include "pool.h"
#include <new>

PUNK_ENGINE_BEGIN
namespace Core {

    template<class T>
    class Poolable
    {
        static Pool pool;
    public:
        static void* operator new (size_t)
        {
            void* buf = pool.Alloc(sizeof(T));
            return buf;
        }

        static void operator delete (void* obj)
        {
            //((T*)obj)->~T();
            pool.Free(obj);
        }

        static void ClearPool()
        {
            pool.Clear();
        }
    };

    template<class T> Pool Poolable<T>::pool;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_POOLABLE
