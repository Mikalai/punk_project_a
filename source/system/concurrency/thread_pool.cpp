#include "atomic.h"
#include "work_item.h"
#include "thread_pool.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class ThreadPoolWorkItem : public WorkItem{
    public:
        void Run(void* data) override {
            ThreadPool* pool = reinterpret_cast<ThreadPool*>(data);
            try
            {
                while (1)
                {
                    if (pool->IsFinish())
                        return;
                    Thread::ThreadData thread_data = pool->GetThreadJob();
                    if (!thread_data.item)
                        return;
                    thread_data.item->Run(thread_data.data);
                    thread_data.item->Complete();
                }
            }
            catch (...)
            {
            }
        }
    };

	ThreadPool::ThreadPool(int thread_count)
	{
		Init(thread_count);
	}

	ThreadPool::~ThreadPool()
	{
        while (m_work_items.empty()) {
            ThreadPoolWorkItem* item = m_work_items.back();
            while (!item->IsComplete());
            delete item;
            m_work_items.pop_back();
        }
	}

	void ThreadPool::Init(int thread_count)
	{
        m_finish.Store(0);

		m_threads.resize(thread_count);
		for(auto it = m_threads.begin(); it != m_threads.end(); ++it)
		{
            Thread& thread = *it;
            ThreadPoolWorkItem* item = new ThreadPoolWorkItem;
            m_work_items.push_back(item);
            thread.Start(item, (void*)this);
		}
	}

    Thread::ThreadData ThreadPool::GetThreadJob()
	{
        m_monitor.Lock();
		if (m_jobs.empty())
            m_monitor.Wait();

		if (m_jobs.empty())
            return Thread::ThreadData{};

        Thread::ThreadData data = m_jobs.front();
		m_jobs.pop();
        m_monitor.Unlock();
        return data;
	}

    void ThreadPool::EnqueueWorkItem(WorkItem *job, void* data)
	{
        m_monitor.Lock();
        Thread::ThreadData thread_data{job, data};
        m_jobs.push(thread_data);
        m_monitor.Pulse();
        m_monitor.Unlock();
	}

	void ThreadPool::Lock()
	{
        m_monitor.Lock();
	}

	void ThreadPool::Unlock()
	{
        m_monitor.Unlock();
	}

	void ThreadPool::Join()
	{
        m_finish.FetchAndAddOrdered(1);
        for (size_t i = 0; i != m_threads.size(); ++i)
            m_threads[i].Join();
	}

	bool ThreadPool::IsFinish()
	{        
        return m_finish.TestAndSetOrdered(1, 1);
	}

	int ThreadPool::HasJobs()
	{
        m_monitor.Lock();
		int tasks = m_jobs.size();
        m_monitor.Unlock();
		return tasks;
	}

}
PUNK_ENGINE_END
