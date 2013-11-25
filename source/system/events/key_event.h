#ifndef KEY_CHAR_EVENT_H
#define KEY_CHAR_EVENT_H

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API KeyEvent : public Event
    {        
        KeyEvent(const KeyEvent&);
    public:
        KeyEvent();
        int key;
		int repeat_count;
		int scan_code;
		bool isExtended;
		bool isAltPressed;
		bool prevState;
		bool transitionState;
        const Core::String ToString() const override;
    };
}
PUNK_ENGINE_END

#endif // KEY_CHAR_EVENT_H
