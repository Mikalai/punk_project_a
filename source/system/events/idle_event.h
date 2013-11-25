#ifndef IDLE_EVENT_H
#define IDLE_EVENT_H

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API IdleEvent : public Event
    {        
        IdleEvent(IdleEvent&);
    public:
		IdleEvent();		
		double elapsed_time_s;
        const Core::String ToString() const override;
    };	
}
PUNK_ENGINE_END
#endif // IDLE_EVENT_H
