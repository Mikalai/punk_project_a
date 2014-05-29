#ifndef _H_ITHREAD_POOL
#define _H_ITHREAD_POOL

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System {

	class WorkItem;

	class IThreadPool {
	public:
		virtual void EnqueueWorkItem(WorkItem* job, void* data = nullptr, bool auto_del = false) = 0;
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
		virtual void Join() = 0;
		virtual bool IsFinish() = 0;
		virtual int HasJobs() = 0;
	};

	PUNK_ENGINE_API IThreadPool* GetThreadPool();
}
PUNK_ENGINE_END
#endif	//	_H_ITHREAD_POOL