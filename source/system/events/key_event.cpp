#include "key_event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    KeyEvent::KeyEvent()
    {
        eventCode = EVENT_KEY_CHAR;
    }

    const Core::String KeyEvent::ToString() const
	{
        return Core::String("Code: %d; Type: KEY_CHAR", eventCode);
	}
}
PUNK_ENGINE_END
