#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API MouseEvent : public Event
    {        
    public:        
        MouseEvent();
        int x, y;
		int x_prev, y_prev;
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

#endif // MOUSE_EVENT_H
