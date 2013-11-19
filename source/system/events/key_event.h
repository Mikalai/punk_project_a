#ifndef KEY_CHAR_EVENT_H
#define KEY_CHAR_EVENT_H

#include "event.h"

namespace System
{
    class PUNK_ENGINE_API KeyEvent : public Event, public Poolable<KeyEvent>
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
		virtual string ToString();
    };
}

#endif // KEY_CHAR_EVENT_H
