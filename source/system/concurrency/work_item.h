#ifndef WORK_ITEM_H
#define WORK_ITEM_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace System {
    class WorkItem
    {
    public:
        virtual void Run(void* data) = 0;
        void Complete();
        bool IsComplete();
    private:
        bool m_complete {false};
    };
}
PUNK_ENGINE_END

#endif // WORK_ITEM_H
