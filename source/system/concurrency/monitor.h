#ifndef PUNK_SYSTEM_MONITOR
#define PUNK_SYSTEM_MONITOR

#ifdef _WIN32
#include <Windows.h>
#elif defined __gnu_linux__
#include <pthread.h>
#endif
#include <mutex>
#include <condition_variable>

#include <config.h>

//#ifdef _WIN32
//struct CONDITION_VARIABLE {
//    char data[4096];
//};

//typedef CONDITION_VARIABLE* PCONDITION_VARIABLE;
//#endif

PUNK_ENGINE_BEGIN
namespace System
{
    class Monitor
    {
    public:
        Monitor();
        ~Monitor();
        void Lock();
        bool TryLock();
        void Unlock();
        void Wait();
        void Pulse();
        void PulseAll();

    private:
#ifdef _WIN32
    CONDITION_VARIABLE m_conditional_variable;
    CRITICAL_SECTION m_mutex;
#elif defined __gnu_linux__
    pthread_cond_t m_condition_variable;
    pthread_mutex_t m_mutex;
#endif

    };
}
PUNK_ENGINE_END

#endif  //  PUNK_SYSTEM_MONITOR
