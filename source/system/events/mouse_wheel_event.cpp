#include "mouse_wheel_event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    MouseWheelEvent::MouseWheelEvent()
    {
        eventCode = EVENT_MOUSE_WHEEL;
    }

    const Core::String MouseWheelEvent::ToString() const
	{
        return Core::String("Code: {0}; Type: MOUSE_WHEEL; delta: {1}; x: {2}; y: {3}; x_prev: {4}; y_prev: {5};")
                .arg(eventCode).arg(delta).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
PUNK_ENGINE_END
