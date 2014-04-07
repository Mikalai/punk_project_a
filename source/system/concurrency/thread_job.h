#ifndef _H_THREAD_JOB
#define _H_THREAD_JOB

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System
{
	class ThreadPool;

	class PUNK_ENGINE_API ThreadJob
	{
	public:	
		ThreadJob();	
		void Run();
		bool IsComplete();
        void Terminate();
	private:
		bool m_complete;
		ThreadPool* m_pool;
		friend class ThreadPool;
	protected:
        virtual void RunThread() = 0;
	};
}
PUNK_ENGINE_END

#endif
