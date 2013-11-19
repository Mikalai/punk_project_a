#include "mouse_event.h"

namespace System
{
    MouseEvent::MouseEvent()
    {
        eventCode = EVENT_MOUSE_BUTTON;
    }

    const string MouseEvent::ToString()
	{
        return string("Code: {0}; Type: MOUSE_LBTNUP; x: {1}; y: {2}; x_prev: {3}; y_prev: {4};")
                .arg(eventCode).arg(x).arg(y).arg(x_prev).arg(y_prev);
	}
}
