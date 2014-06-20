#include "mouse_hoover_event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    MouseHooverEvent::MouseHooverEvent()
    {
		eventCode = EVENT_MOUSE_HOOVER;
    }

    const Core::String MouseHooverEvent::ToString() const
	{
        return Core::String("Code: {0}; Type: MOUSE_HOOVER; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
PUNK_ENGINE_END
