#include "model_time_step_event.h"

PUNK_ENGINE_BEGIN
namespace System
{
	ModelTimeStepEvent::ModelTimeStepEvent()
    {
//		eventCode = EVENT_MODEL_TIME_STEP;
    }

    const Core::String ModelTimeStepEvent::ToString() const
	{
        return Core::String("Code: {0}; Type: MODEL_TIME_STEP; Step: {1}").arg(eventCode).arg(elapsed_time_ms);
	}
}
PUNK_ENGINE_END
