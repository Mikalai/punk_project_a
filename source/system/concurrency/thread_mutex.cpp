#include <system/errors/module.h>
#include "thread_mutex.h"

PUNK_ENGINE_BEGIN
namespace System
{
	ThreadMutex::ThreadMutex()
	{
		if (!Create())
			throw Error::SystemException("Can't initialize thread mutex");
	}	

	ThreadMutex::~ThreadMutex()
	{
		Destroy();
	}

	bool ThreadMutex::Create()
	{
#ifdef _WIN32
		return InitializeCriticalSectionAndSpinCount(&m_mutex, 4000) != FALSE;
#elif defined __gnu_linux__
        pthread_mutex_init(&m_mutex, nullptr);
        return true;
#endif
	}

	void ThreadMutex::Destroy()
	{
#ifdef _WIN32
		DeleteCriticalSection(&m_mutex);
#elif defined __gnu_linux__
        pthread_mutex_destroy(&m_mutex);
#endif
	}

	void ThreadMutex::Lock()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_mutex);
#elif defined __gnu_linux__
        pthread_mutex_lock(&m_mutex);
#endif
	}

	bool ThreadMutex::TryLock()
	{
#ifdef _WIN32
		return TryEnterCriticalSection(&m_mutex) != FALSE;
#elif defined __gnu_linux__
        return pthread_mutex_trylock(&m_mutex) == 0;
#endif
	}

	void ThreadMutex::Unlock()
	{
#ifdef _WIN32
		LeaveCriticalSection(&m_mutex);
#elif  defined __gnu_linux__
        pthread_mutex_unlock(&m_mutex);
#endif
	}
}
PUNK_ENGINE_END
