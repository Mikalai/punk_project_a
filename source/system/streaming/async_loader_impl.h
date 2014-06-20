#ifndef _H_PUNK_SYSTEM_ASYNC_LOADER
#define _H_PUNK_SYSTEM_ASYNC_LOADER

#include <memory>
#include <deque>
#include <vector>
#include <config.h>
#include <system/concurrency/thread_mutex.h>
#include <system/concurrency/semaphore.h>
#include <system/concurrency/thread.h>
#include "resource_request.h"
#include "async_loader.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_LOCAL AsyncLoaderImpl : public AsyncLoader
	{
	public:
        AsyncLoaderImpl(int num_process_threads);
        virtual ~AsyncLoaderImpl();
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result);
        virtual unsigned MainThreadProc(unsigned num_to_process);
		unsigned FileIOThreadProc();
		unsigned ProcessingThreadProc();		

	private:
		std::deque<ResourceRequest> m_io_queue;
		std::deque<ResourceRequest> m_process_queue;
		std::deque<ResourceRequest> m_render_queue;
		bool m_io_done_flag;
		bool m_process_done_flag;
		bool m_global_done_flag;
		ThreadMutex m_io_queue_mutex;
		ThreadMutex m_process_queue_mutex;
		ThreadMutex m_render_queue_mutex;
		Semaphore m_io_thread_semaphore;
		Semaphore m_process_thread_semaphore;
		Thread m_io_thread;
		std::vector<Thread> m_process_threads;
		unsigned m_num_io_requests;
		unsigned m_num_process_requests;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_ASYNC_LOADER
