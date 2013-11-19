#include "key_event.h"

namespace System
{
    KeyEvent::KeyEvent()
    {
        eventCode = EVENT_KEY_CHAR;
    }

    string KeyEvent::ToString()
	{
		return string("Code: %d; Type: KEY_CHAR", eventCode);
	}
}
