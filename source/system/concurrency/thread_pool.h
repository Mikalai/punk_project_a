#ifndef _H_THREAD_POOL
#define _H_THREAD_POOL

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#endif

#include <vector>
#include <stack>
#include <queue>

#include <config.h>
#include "work_item.h"
#include "thread.h"
#include "monitor.h"
#include "atomicint.h"
#include "ithread_pool.h"

PUNK_ENGINE_BEGIN
namespace System {
    class ThreadPoolWorkItem;

    class PUNK_ENGINE_LOCAL ThreadPool : public IThreadPool {
	public:
		ThreadPool(int threads_count = 4);
		virtual ~ThreadPool();
        void EnqueueWorkItem(WorkItem* job, void* data = nullptr, bool auto_del = false) override;
		void Lock() override;
		void Unlock() override;
		void Join() override;
		bool IsFinish() override;
		int HasJobs() override;

	private:
		void Init(int thread_count);
        Thread::ThreadData GetThreadJob();
        friend class ThreadPoolWorkItem;

    private:
        std::queue<Thread::ThreadData> m_jobs;
        ThreadPool(const ThreadPool& pool);
        ThreadPool& operator = (const ThreadPool&);

        std::vector<Thread> m_threads;
        std::vector<ThreadPoolWorkItem*> m_work_items;
        Thread m_own_thread;
        Monitor m_monitor;

        AtomicInt m_finish;
	};
}
PUNK_ENGINE_END

#endif
