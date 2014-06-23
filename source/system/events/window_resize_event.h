#ifndef _H_PUNK_WINDOW_RESIZE
#define _H_PUNK_WINDOW_RESIZE

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API WindowResizeEvent : public Event
    {        
        WindowResizeEvent(const WindowResizeEvent&);
    public:
		WindowResizeEvent();
		virtual ~WindowResizeEvent();

        bool minimized;
		bool restored;
        int width, height;
		
        const Core::String ToString() const override;
    };
}
PUNK_ENGINE_END

#endif
