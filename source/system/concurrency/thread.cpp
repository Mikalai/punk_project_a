#ifdef _WIN32
#include <process.h>
#elif defined __gnu_linux__
#include <time.h>
#endif

#include <system/logger/module.h>
#include <system/errors/module.h>
#include "work_item.h"
#include "thread.h"

PUNK_ENGINE_BEGIN
namespace System
{
    Thread::~Thread()
    {
        Destroy();
    }

#ifdef _WIN32
        unsigned thread_func(void* data)
#elif defined __gnu_linux__
        void* thread_func(void* data = 0)
#endif
        {
            Thread::ThreadData* thread_data = (Thread::ThreadData*)data;
            WorkItem* work_item = thread_data->item;
            void* work_data = thread_data->data;
            delete thread_data;

            try {
                work_item->Run(work_data);
            }
            catch(Error::SystemException& e) {
                GetDefaultLogger()->Error(e.Message());
            }
            catch(...) {
                GetDefaultLogger()->Error("Unknown error occured in the thread_func");
            }
        }

#ifdef _WIN32
    bool Thread::Start(WorkItem* work_item, void* data)
    {
        if (Handle() != NULL)
            return false;
        ThreadData* thread_data = new ThreadData;
        thread_data->item = work_item;
        thread_data->data = data;
        Handle() = (HANDLE)_beginthreadex(0, m_stack, thread_func, thread_data, CREATE_SUSPENDED, 0);
        if (Handle() != INVALID_HANDLE_VALUE)
            return true;
        return false;
    }
#endif	//	_WIN32

#ifdef __gnu_linux__
    bool Thread::Create(void* (PUNK_STDCALL *thread_func)(void *), void *data, unsigned stack)
    {
        bool result = false;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, stack);
        result = pthread_create(ThreadHandle(), &attr, thread_func, data) != 0;
        pthread_attr_destroy(&attr);
        return result;
    }
#endif

    bool Thread::Join()
    {
#ifdef _WIN32
        return WaitForSingleObject(Handle(), INFINITE) != WAIT_FAILED;
#elif defined __gnu_linux__
        void* result;
        return pthread_join(*ThreadHandle(), &result) == 0;
#endif
    }

    bool Thread::Resume()
    {
#ifdef _WIN32
        return ResumeThread(Handle()) != (DWORD)-1;
#elif   defined __gnu_linux__
        return false;
#endif
    }

    bool Thread::Destroy()
    {
#ifdef _WIN32
        if (Handle())
        {
            CloseHandle(Handle());
            Handle() = NULL;
        }
        return true;
#elif defined __gnu_linux__
        //  TODO: seems nothing should be placed here
        return false;
#endif
    }

    Thread Thread::GetOwnThread()
    {
#ifdef _WIN32
        Thread result;
        result.Handle() = GetCurrentThread();
        return result;
#elif defined __gnu_linux__
        Thread result;
        *result.ThreadHandle() = pthread_self();
        return result;
#endif
    }

    void Thread::Sleep(unsigned time)
    {
#ifdef _WIN32
        ::Sleep(time);
#elif defined __gnu_linux__
        timespec t, rem;
        t.tv_sec = time / 1000;
        t.tv_nsec = (time % 1000) * 1000000;
        nanosleep(&t, &rem);
#endif
    }
}
PUNK_ENGINE_END
