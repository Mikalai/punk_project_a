#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include "config.h"
#include "event.h"

PUNK_ENGINE_BEGIN
namespace System {
    class PUNK_ENGINE_API MouseMoveEvent : public Event
    {
        MouseMoveEvent(const MouseMoveEvent&);
    public:
        MouseMoveEvent();
        int x, y;
        int x_prev, y_prev;
        int delta;
        bool controlKey : 1;
        bool leftButton : 1;
        bool middleButton : 1;
        bool rightButton  : 1;
        bool shiftButton  : 1;
        bool xbutton1 : 1;
        bool xbutton2 : 1;

        const Core::String ToString() const override;
    };
}
PUNK_ENGINE_END
#endif // MOUSE_MOVE_EVENT_H
