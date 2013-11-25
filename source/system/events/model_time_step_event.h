#ifndef MODEL_TIME_STEP_H
#define MODEL_TIME_STEP_H

#include "event.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API ModelTimeStepEvent : public Event
    {        
        ModelTimeStepEvent(ModelTimeStepEvent&);
    public:
		ModelTimeStepEvent();
		unsigned elapsed_time_ms;
        const Core::String ToString() const override;
    };	
}
PUNK_ENGINE_END

#endif // MODEL_TIME_STEP_H
