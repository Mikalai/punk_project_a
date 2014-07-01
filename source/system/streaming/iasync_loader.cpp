#include <memory>
#include <deque>
#include <vector>
#include <config.h>
#include <system/concurrency/thread_mutex.h>
#include <system/concurrency/semaphore.h>
#include <system/concurrency/thread.h>
#include "resource_request.h"
#include "core/iobject_impl.h"
#include "iasync_loader.h"

#ifdef __gnu_linux__
#include <limits.h>
#else
#include <limits>
//#define LONG_MAX std::numeric_limits<long>::max()
#endif

#include <system/concurrency/work_item.h>
#include "engine_objects.h"
#include "data_loader.h"
#include "data_processor.h"

PUNK_ENGINE_BEGIN
namespace System
{
	class AbstractDataLoader;
	class AbstractDataProcessor;

	class PUNK_ENGINE_LOCAL AsyncLoaderImpl : public IAsyncLoader
	{
	public:
		AsyncLoaderImpl(int num_process_threads);
		virtual ~AsyncLoaderImpl();
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAsyncLoader
		int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) override;
		unsigned MainThreadProc(unsigned num_to_process) override;
		unsigned FileIOThreadProc();
		unsigned ProcessingThreadProc();

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
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


	class IoThreadWorkItem : public WorkItem {
	public:
		void Run(void* data) override
		{
			if (data == nullptr)
				return;
			reinterpret_cast<AsyncLoaderImpl*>(data)->FileIOThreadProc();
		}
	};

	class ProcessThreadWorkItem : public WorkItem {
	public:
		void Run(void* data) override {
			if (data == nullptr)
				return;
			reinterpret_cast<AsyncLoaderImpl*>(data)->ProcessingThreadProc();
		}
	};

	void AsyncLoaderImpl::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAsyncLoader });
	}

	std::uint32_t AsyncLoaderImpl::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t AsyncLoaderImpl::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	AsyncLoaderImpl::AsyncLoaderImpl(int num_process_threads)
	{
		static IoThreadWorkItem io_thread_work_item;
		static std::vector<ProcessThreadWorkItem> process_thread_work_item(num_process_threads);
		m_global_done_flag = false;
		m_io_thread_semaphore.Create(LONG_MAX);
		m_process_thread_semaphore.Create(LONG_MAX);

		m_process_threads.resize(num_process_threads);
		int i = 0;
		for (auto it = m_process_threads.begin(); it != m_process_threads.end(); ++it)
		{
			it->Start(&process_thread_work_item[i], (void*)this);
			it->Resume();
			i++;
		}

		m_io_thread.Start(&io_thread_work_item, (void*)this);
		m_io_thread.Resume();
	}

	/**
	*	This method initiates process of loading data from hard drive
	*	that finaly should lead to the uploading data to the device
	*	memory
	*/
	int AsyncLoaderImpl::AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result)
	{
		int res = -1;
		//	check input data
		if (!loader || !processor)
			return res;

		//	create initial request
		ResourceRequest request;
		request.m_loader = loader;
		request.m_processor = processor;
		request.m_result = result;
		request.m_valid_flag = true;
		request.m_task = ResourceRequest::LOAD;
		request.on_end_callback = nullptr;
		request.m_on_end_data = nullptr;

		//	add request to input queue
		m_io_queue_mutex.Lock();
		m_io_queue.push_back(request);
		res = (int)m_io_queue.size() - 1;
		m_io_queue_mutex.Unlock();

		//	allow io thread to do job
		m_io_thread_semaphore.Release();

		return res;
	}

	/*
	*	This method works in separate thread and can load
	*	data from hard driver using data loader
	*	and can upload data from host memory to device memory
	*	using data processor
	*/
	unsigned AsyncLoaderImpl::FileIOThreadProc()
	{
		ResourceRequest request;
		m_io_done_flag = false;
		while (!m_global_done_flag)
		{
			//	wait till the task will be added
			m_io_thread_semaphore.Wait();

			//	check if program terminated
			if (m_global_done_flag)
				break;

			//	fetch request using critical section
			m_io_queue_mutex.Lock();
			request = m_io_queue.front();
			m_io_queue.pop_front();
			m_io_queue_mutex.Unlock();

			//	check requested operation
			//	LOAD - from hard drive data loading
			if (ResourceRequest::LOAD == request.m_task)
			{
				//	check if the request is valid
				if (request.m_valid_flag)
				{
					auto res = request.m_loader->Load();
					//	if error, mark request as invalid
					if (StreamingStepResult::STREAM_ERROR == res)
					{
						request.m_valid_flag = false;
					}
					//	if try again, mark add request to the io queue again, and continue
					else if (StreamingStepResult::STREAM_TRY_AGAIN == res)
					{
						m_io_queue_mutex.Lock();
						m_io_queue.push_back(request);
						m_io_queue_mutex.Unlock();
						m_io_thread_semaphore.Release();
						continue;
					}
				}

				//	if request is not valid we simply bypass it to the next stag, because only
				//	somewhere their it will be destroyed
				m_process_queue_mutex.Lock();
				m_process_queue.push_back(request);
				m_process_queue_mutex.Unlock();

				//	allow process threads to next tasks to the request
				m_process_thread_semaphore.Release();
			}

			//	we need to copy data from host memory to the device memory
			else if (ResourceRequest::COPY_TO_DEVICE == request.m_task)
			{
				//	check is request is still valid
				if (request.m_valid_flag)
				{
					//	try to copy data to device memory
					auto res = request.m_processor->CopyToResource();
					//	mark invalid is error
					if (StreamingStepResult::STREAM_ERROR == res)
					{
						//	if troubles invalidate request
						request.m_valid_flag = false;
					}
					else if (StreamingStepResult::STREAM_TRY_AGAIN == res)
					{
						m_io_queue_mutex.Lock();
						m_io_queue.push_back(request);
						m_io_queue_mutex.Unlock();
						m_io_thread_semaphore.Release();
						continue;
					}
				}

				//	unlock this resource, seems that it means that data
				//	is in device memory or error was now, and we don't need request to exist any
				//	more
				request.m_task = ResourceRequest::UNLOCK;

				//	add request to the main thread queue
				m_render_queue_mutex.Lock();
				m_render_queue.push_back(request);
				m_render_queue_mutex.Unlock();
			}
		}

		m_io_done_flag = true;
		return m_io_done_flag;
	}

	unsigned AsyncLoaderImpl::ProcessingThreadProc()
	{
		ResourceRequest request;
		//	set process thread done flag as false
		m_process_done_flag = false;

		//	if program is not end
		while (!m_global_done_flag)
		{
			//	wait till the tasks in processing queue
			m_process_thread_semaphore.Wait();
			if (m_global_done_flag)
				break;

			//	fetch request from the processing queue
			m_process_queue_mutex.Lock();
			request = m_process_queue.front();
			m_process_queue.pop_front();
			m_process_queue_mutex.Unlock();

			//	check if request is still valid
			if (request.m_valid_flag)
			{
				void* data = nullptr;
				unsigned size = 0;
				//	decompress data using loader
				auto res = request.m_loader->Decompress(&data, &size);
				//	if all ok continue decompression
				if (StreamingStepResult::STREAM_OK == res)
				{
					// process data using processor
					res = request.m_processor->Process(data, size);
					//	if failed set request is invalid
					if (StreamingStepResult::STREAM_ERROR == res)
					{
						request.m_valid_flag = false;
					}
					//	try again if required
					else if (StreamingStepResult::STREAM_TRY_AGAIN == res)
					{
						m_process_queue_mutex.Lock();
						m_process_queue.push_back(request);
						m_process_queue_mutex.Unlock();
						m_process_thread_semaphore.Release();
					}
				}
				//	try again if required
				else if (res == StreamingStepResult::STREAM_TRY_AGAIN)
				{
					m_process_queue_mutex.Lock();
					m_process_queue.push_back(request);
					m_process_queue_mutex.Unlock();
					m_process_thread_semaphore.Release();
				}
				//	if decompress failed set request as invalid
				else if (res == StreamingStepResult::STREAM_ERROR)
				{
					request.m_valid_flag = false;
				}
			}

			//	lock request, that means we are gonna copy data from
			//	host to device in the render thread (main thread)
			request.m_task = ResourceRequest::LOCK;

			//	add request to the render thread queue
			m_render_queue_mutex.Lock();
			m_render_queue.push_back(request);
			m_render_queue_mutex.Unlock();
		}

		//	mark thread as finished
		m_process_done_flag = true;
		return m_process_done_flag;
	}

	/**
	*	This is called from main thread.
	*/
	unsigned AsyncLoaderImpl::MainThreadProc(unsigned num_to_process)
	{
		ResourceRequest request;
		m_render_queue_mutex.Lock();
		unsigned max_count = (unsigned)m_render_queue.size();
		m_render_queue_mutex.Unlock();

		for (unsigned i = 0; i < num_to_process && i < max_count; ++i)
		{
			m_render_queue_mutex.Lock();
			request = m_render_queue.front();
			m_render_queue.pop_front();
			m_render_queue_mutex.Unlock();

			//	if command is to lock the object we will try to do that
			if (ResourceRequest::LOCK == request.m_task)
			{
				if (request.m_valid_flag)
				{
					//	try to lock is request is still valid
					auto res = request.m_processor->LockDeviceObject();
					//	if there was not enough resource now, try again later
					if (StreamingStepResult::STREAM_TRY_AGAIN == res)
					{
						m_render_queue_mutex.Lock();
						m_render_queue.push_back(request);
						m_render_queue_mutex.Unlock();
						continue;
					}
					//	if it was a complete fail, just mark this request is not valid
					else if (StreamingStepResult::STREAM_ERROR == res)
					{
						request.m_valid_flag = false;
					}
				}

				//	it doesn't mater what is the validity state of the resource
				//	we have to push it through the datapah pipeling

				//	operation for io thread to copy data to device
				request.m_task = ResourceRequest::COPY_TO_DEVICE;
				m_io_queue_mutex.Lock();
				m_io_queue.push_back(request);
				m_io_queue_mutex.Unlock();

				//	allow io thread to do the job
				m_io_thread_semaphore.Release();
			}
			//	if task is unlock, it means that we have finished loading
			//	and cooking resource
			else if (ResourceRequest::UNLOCK == request.m_task)
			{
				if (request.m_valid_flag)
				{
					//	if object is valid, unloc resource
					auto res = request.m_processor->UnlockDeviceObject();
					if (StreamingStepResult::STREAM_ERROR == res)
					{
						request.m_valid_flag = false;
					}
					else if (StreamingStepResult::STREAM_TRY_AGAIN == res)
					{
						m_render_queue_mutex.Lock();
						m_render_queue.push_back(request);
						m_render_queue_mutex.Unlock();
						continue;
					}
				}

				//	if request is already unlocked and in the main thread, it means
				//	its loading, copying and all the other staff complete

				delete request.m_loader;
				request.m_loader = nullptr;
				delete request.m_processor;
				request.m_processor = nullptr;
				//	wite flag back if requred
				if (request.m_result)
					*request.m_result = request.m_valid_flag;	//	OK
			}
		}
		return 0;
	}

	/**
	*	This method will terminate io and processing threads
	*/
	AsyncLoaderImpl::~AsyncLoaderImpl()
	{
		//	declare end of work
		m_global_done_flag = true;

		//	release semaphores to allow them
		//	checking global done flag (which is true now)
		//	 that will allow thread to commit suicide
		//	successfuly without any TerminateThread procedures
		m_io_thread_semaphore.Release();
		m_process_thread_semaphore.Release();

		//	Wait till thread are done
		while (!m_io_done_flag || !m_process_done_flag)
		{
			//	Confusing a bit, but still should work
			System::Thread::Sleep(100);
		}

		//	destroy all semaphores
		m_io_thread_semaphore.Destroy();
		m_process_thread_semaphore.Destroy();

		//	destroy all mutexes
		m_io_queue_mutex.Destroy();
		m_process_queue_mutex.Destroy();

		//	destroy all process handles
		for (auto it = m_process_threads.begin(); it != m_process_threads.end(); ++it)
			it->Destroy();

		//	destroy io thread
		m_io_thread.Destroy();
	}

	extern PUNK_ENGINE_API IAsyncLoader* CreateAsyncLoader(int num_threads) {
		return new AsyncLoaderImpl(num_threads);
	}

	extern PUNK_ENGINE_API void DestroyAsyncLoader(IAsyncLoader* value) {
		AsyncLoaderImpl* v = dynamic_cast<AsyncLoaderImpl*>(value);
		delete v;
	}
}
PUNK_ENGINE_END

