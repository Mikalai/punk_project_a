#include "thread_job.h"
#include "thread_pool.h"

PUNK_ENGINE_BEGIN
namespace System
{
	ThreadJob::ThreadJob()
	{
		m_complete = false;
	}

	bool ThreadJob::IsComplete()
	{
		m_pool->Lock();
		bool result = m_complete;
		m_pool->Unlock();
		return result;
	}

	void ThreadJob::Run()
	{
		RunThread();
	}
}
PUNK_ENGINE_END
