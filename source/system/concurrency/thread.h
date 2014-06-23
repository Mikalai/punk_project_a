#ifndef _H_PUNK_THREAD
#define _H_PUNK_THREAD

#include <config.h>
#include <cstdint>
#include "os_handle.h"

PUNK_ENGINE_BEGIN
namespace System {

    class WorkItem;

    class PUNK_ENGINE_API Thread : public OsHandle {
	public:
		bool Join();
		bool Resume();
		bool Destroy();
        bool Start(WorkItem* work_item, void* data);
		//bool Terminate();
		~Thread();

        static Thread GetOwnThread();
        /**
         * @brief Sleep. Force to sleep current thread for time milliseconds.
         * @param time
         */
        static void Sleep(unsigned time);

        struct ThreadData {
            WorkItem* item;
            void* data;
            bool delete_item;
        };

    private:
        std::uint32_t m_stack {4096};
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_THREAD
