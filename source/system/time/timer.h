#ifndef _H_PUNK_SYSTEM_TIMER
#define _H_PUNK_SYSTEM_TIMER

#include <memory>
#include "core/object.h"
#include "timer_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class TimerImpl;

	/**
	*	Timer is used for strict time count
	*/
    class PUNK_ENGINE_LOCAL Timer final : public ITimer, public Core::Object
    {
    public:
        Timer();
		~Timer();

        double GetCurrentTime() const override;
        double GetElapsedSeconds() const override;
        double GetElapsedMiliseconds() const override;
        double Reset() override;

	private:
		Timer(const Timer&);
		Timer& operator = (const Timer&);

        TimerImpl* impl {nullptr};

        PUNK_OBJECT(Timer)
    };
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_TIMER
