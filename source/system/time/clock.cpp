#include "clock.h"

#ifdef __GNUC__
#include <time.h>
#endif

#include <stdio.h>
#include <String.h>

PUNK_ENGINE_BEGIN
namespace System {

	Clock::Clock()
		: m_container{ this, Core::GetRootObject() }
	{                
        m_time = 0;
        m_us = 0;

#ifdef __linux__
        m_date = *localtime(&m_time);
#elif defined MSVS
        _localtime64_s(&m_date, &m_time);
#endif
	}

    Clock::~Clock()
    {
    }

    /*const Core::String Clock::ToString() const
	{
#ifdef _MSC_VER
		wchar_t buffer[256];
		_wasctime_s(buffer, 256, &m_date);
		buffer[24] = 0;
        return Core::String(buffer);
#elif defined __linux__
        Core::String str(asctime(&m_date));
        str[24] = 0;
        return str;
#endif        
	}*/

	int Clock::Hour() const
	{
		return m_date.tm_hour;
	}

	int Clock::Minute() const
	{
		return m_date.tm_min;
	}

	int Clock::Second() const
	{
		return m_date.tm_sec;
	}

    int Clock::Month() const
    {
        return m_date.tm_mon;
    }

	int Clock::MonthDay() const
	{
		return m_date.tm_mday;
	}

	int Clock::Year() const
	{
		return m_date.tm_year;
	}

	int Clock::WeekDay() const
	{
		return m_date.tm_wday;
	}

	int Clock::YearDay() const
	{
		return m_date.tm_yday;
	}

	int Clock::MilliSecond() const
	{
		return (int)m_us;
	}

    std::int64_t Clock::Now()
	{
		return m_time;
	}

    void Clock::Advance(std::int64_t dt)
	{
		m_us += dt;
		m_time += m_us / 1000000;
		m_us %= 1000000;
#ifdef MSVS
		_gmtime64_s(&m_date, &m_time);
#elif defined __linux__
        m_date = *gmtime(&m_time);
#endif
	}

	int64_t Clock::SysTimeAsSecondsFromJanuary_1970_1()
	{
		time_t t;
		time(&t);
		return t;
	}

    const Core::String Clock::SysTimeAsUTC()
	{
#ifdef _MSC_VER
		char buffer[32];
		__time32_t t;
		_time32(&t);
		tm _tm;
		_gmtime32_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
        // replace new line in the time Core::String. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
        return Core::String(buffer);
#elif defined __linux__
        time_t t;
        time(&t);
        tm _tm = *gmtime(&t);
        Core::String str(asctime(&_tm));
        // replace new line in the time Core::String. 24 because total length 26 and it is STANDARD
        str[24] = L'\0';
        return str;
#endif
	}

    const Core::String Clock::SysTimeNowAsLocal()
	{
#ifdef _MSC_VER
		char buffer[32];
		__time32_t t;
		_time32(&t);
		tm _tm;
		_localtime32_s(&_tm, &t);
		asctime_s(buffer, 32, &_tm);
        // replace new line in the time Core::String. 24 because total length 26 and it is STANDARD
		buffer[24] = '\0';
        return Core::String(buffer);
#else
        time_t t;
        time(&t);
        tm _tm = *localtime(&t);
        Core::String str(asctime(&_tm));
        // replace new line in the time Core::String. 24 because total length 26 and it is STANDARD
        str[19] = 0;
        return Core::String(&str[11], &str[19] - &str[11]);
#endif
	}

	void Clock::Set(int Year, int Month, int Day, int Hour, int Min, int Sec)
	{
		memset(&m_date, 0, sizeof(m_date));
		m_date.tm_year = Year;
		m_date.tm_mon = Month;
		m_date.tm_mday = Day;
		m_date.tm_hour = Hour;
		m_date.tm_min = Min;
		m_date.tm_sec = Sec;

#ifdef MSVS
		m_time = _mktime64(&m_date);
		_gmtime64_s(&m_date, &m_time);
#elif defined __linux__
        m_time = mktime(&m_date);
        m_date = *gmtime(&m_time);
#endif
	}
    /*
        void Clock::Store(Buffer& buffer)
        {
            buffer.WriteSigned64(m_time);
            buffer.WriteSigned64(m_us);
        }

        void Clock::Restore(Buffer& buffer)
        {
            m_time = buffer.ReadSigned64();
            m_us = buffer.ReadSigned64();
            _gmtime64_s(&m_date, &m_time);
        }*/

    IClock* CreateClock() {
        return new Clock();
    }

    void DestroyClock(IClock* value) {
        Clock* clock = dynamic_cast<Clock*>(value);
        delete clock;
    }
}
PUNK_ENGINE_END
