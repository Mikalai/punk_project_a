#include "idle_event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    IdleEvent::IdleEvent()
    {
        eventCode = EVENT_IDLE;
    }

    const Core::String IdleEvent::ToString() const
	{
        return Core::String("Code: %d; Type: IDLE", eventCode);
	}
}
PUNK_ENGINE_END
