#ifndef CLOCK_INTERFACE_H
#define CLOCK_INTERFACE_H

#include <cstdint>
#include "string/string.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API IClock
    {
    public:
        virtual int64_t Now() = 0;
        virtual void Advance(int64_t us) = 0;
        virtual const Core::String ToString() const = 0;
        virtual int Year() const = 0;
        virtual int Month() const = 0;
        virtual int MonthDay() const = 0;
        virtual int WeekDay() const = 0;
        virtual int YearDay() const = 0;
        virtual int Hour() const = 0;
        virtual int Minute() const = 0;
        virtual int Second() const = 0;
        virtual int MilliSecond() const = 0;
        virtual void Set(int Year, int Month, int Day, int Hour, int Min, int Sec) = 0;
        virtual int64_t SysTimeAsSecondsFromJanuary_1970_1() = 0;
        virtual const Core::String SysTimeAsUTC() = 0;
        virtual const Core::String SysTimeNowAsLocal() = 0;
   };

    PUNK_ENGINE_API IClock* CreateClock();
    PUNK_ENGINE_API void DestroyClock(IClock* value);
}
PUNK_ENGINE_END

#endif // CLOCK_INTERFACE_H
