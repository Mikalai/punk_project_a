#ifndef WORK_ITEM_H
#define WORK_ITEM_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System {
    class PUNK_ENGINE_API WorkItem
    {
    public:
        virtual ~WorkItem() {}
        virtual void Run(void* data) = 0;
        void Complete();
        bool IsComplete();
    private:
        bool m_complete {false};
    };
}
PUNK_ENGINE_END

#endif // WORK_ITEM_H
