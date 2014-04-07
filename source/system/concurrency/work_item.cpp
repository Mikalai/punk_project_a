#include "work_item.h"

PUNK_ENGINE_BEGIN
namespace System {
    void WorkItem::Complete() {
        m_complete = true;
    }

    bool WorkItem::IsComplete() {
        return m_complete;
    }
}
PUNK_ENGINE_END
