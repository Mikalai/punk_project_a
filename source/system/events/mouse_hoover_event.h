#ifndef KEY_MOUSE_HOOVER_EVENT_H
#define KEY_MOUSE_HOOVER_EVENT_H

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API MouseHooverEvent : public Event
    {        
        MouseHooverEvent(const MouseHooverEvent&);
    public:
		MouseHooverEvent();
        int x, y;
		int x_prev, y_prev;
        const Core::String ToString() const override;
    };
}
PUNK_ENGINE_END

#endif // KEY_CHAR_EVENT_H
