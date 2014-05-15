#ifndef _H_PUNK_SYSTEM_CLOCK
#define _H_PUNK_SYSTEM_CLOCK

#ifdef _WIN32
#include <windows.h>
#endif

#include <time.h>
#include "core/object.h"
#include "clock_interface.h"

PUNK_ENGINE_BEGIN
namespace System {
    class PUNK_ENGINE_LOCAL Clock : public IClock {
    public:
		Clock();
        virtual ~Clock();
		/**
		*	Used to retrieve current virtual time value
		*	\returns Current virtual time
		*/
        int64_t Now() override;
		
		/**
		*	Used to increment time of the clock
		*	\param us Time in microseconds
		*/
		void QueryInterface(std::uint64_t type, void**) override;
        void Advance(int64_t us) override;        
        int Year() const override;
        int Month() const override;
        int MonthDay() const override;
        int WeekDay() const override;
        int YearDay() const override;
        int Hour() const override;
        int Minute() const override;
        int Second() const override;
        int MilliSecond() const override;
        void Set(int Year, int Month, int Day, int Hour, int Min, int Sec) override;
        int64_t SysTimeAsSecondsFromJanuary_1970_1();
        const Core::String SysTimeAsUTC() override;
        const Core::String SysTimeNowAsLocal() override;

	private:

        static const int timeSize = 64;
        wchar_t the_time[timeSize];        
#ifdef _WIN32
        __time64_t m_time;
#elif defined __linux__
        time_t m_time;
#endif
        std::int64_t m_us;
		tm m_date;

        PUNK_OBJECT_DEFAULT_IMPL3(Clock)
    };
}
PUNK_ENGINE_END

#endif	//_H_PUNK_SYSTEM_CLOCK
