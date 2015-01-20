#include "monitor.h"

#ifdef _WIN32
#include <windows.h>

#ifndef _MSC_VER
VOID (WINAPI *InitializeConditionVariable)(PCONDITION_VARIABLE ConditionVariable);
BOOL (WINAPI *SleepConditionVariableCS)(PCONDITION_VARIABLE ConditionVariable, PCRITICAL_SECTION CriticalSection, DWORD dwMilliseconds);
//BOOL (WINAPI *SleepConditionVariableSRW)(PCONDITION_VARIABLE ConditionVariable, PSRWLOCK SRWLock, DWORD dwMilliseconds, ULONG Flags);
VOID (WINAPI *WakeAllConditionVariable)(PCONDITION_VARIABLE ConditionVariable);
VOID (WINAPI *WakeConditionVariable)(PCONDITION_VARIABLE ConditionVariable);
#endif	// _MSC_VER

struct InitCnd {

    InitCnd() {
#ifndef _MSC_VER
        HINSTANCE h = LoadLibraryW(L"kernel32.dll");
        InitializeConditionVariable = (VOID (WINAPI *)(PCONDITION_VARIABLE))GetProcAddress(h, "InitializeConditionVariable");
        SleepConditionVariableCS = (BOOL (WINAPI *)(PCONDITION_VARIABLE, PCRITICAL_SECTION, DWORD))GetProcAddress(h, "SleepConditionVariableCS");
        WakeAllConditionVariable = (VOID (WINAPI *)(PCONDITION_VARIABLE))GetProcAddress(h, "WakeAllConditionVariable");
        WakeConditionVariable = (VOID (WINAPI *)(PCONDITION_VARIABLE))GetProcAddress(h, "WakeConditionVariable");
#endif
    }
};

#endif

PUNK_ENGINE_BEGIN
namespace System
{
    Monitor::Monitor()
    {
#ifdef _WIN32
        //static InitCnd g_init_cnd;
        InitializeCriticalSection(&m_mutex);
        InitializeConditionVariable(&m_conditional_variable);
#elif defined __gnu_linux__
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&m_condition_variable, nullptr);
#endif
    }

    Monitor::~Monitor()
    {
#ifdef _WIN32
        DeleteCriticalSection(&m_mutex);
#elif defined __gnu_linux__
        pthread_mutex_destroy(&m_mutex);
#endif
    }

    void Monitor::Lock()
    {
#ifdef _WIN32
        EnterCriticalSection(&m_mutex);
#elif defined __gnu_linux__
        pthread_mutex_lock(&m_mutex);
#endif
    }

    void Monitor::Unlock()
    {
#ifdef _WIN32
        LeaveCriticalSection(&m_mutex);
#elif defined __gnu_linux__
        pthread_mutex_unlock(&m_mutex);
#endif
    }

    void Monitor::Wait()
    {
#ifdef _WIN32
        SleepConditionVariableCS(&m_conditional_variable, &m_mutex, INFINITE);
#elif defined __gnu_linux__
        pthread_cond_wait(&m_condition_variable, &m_mutex);
#endif
    }

    void Monitor::Pulse()
    {
#ifdef _WIN32
        WakeConditionVariable(&m_conditional_variable);
#elif defined __gnu_linux__
        pthread_cond_signal(&m_condition_variable);
#endif
    }

    void Monitor::PulseAll()
    {
#ifdef _WIN32
        WakeAllConditionVariable(&m_conditional_variable);
#elif defined __gnu_linux__
        pthread_cond_broadcast(&m_condition_variable);
#endif
    }
}
PUNK_ENGINE_END
