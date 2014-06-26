#include <stdint.h>
#include <chrono>
#include <system/factory/module.h>
#include "timer.h"

PUNK_ENGINE_BEGIN
namespace System
{
    struct TimerImpl
    {
        std::chrono::high_resolution_clock::time_point m_last_check;

        uint64_t GetTickCount() const
        {
            using namespace std::chrono;
            high_resolution_clock::time_point now = high_resolution_clock::now();
            auto count = now.time_since_epoch().count();
            return count;
        }

        //  returns time in seconds
        double GetTime() const
        {
            using namespace std::chrono;
            auto point = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
			auto value = std::chrono::duration_cast<seconds>(point);
			return (double)value.count();
        }

		double GetElapsedSeconds() const
		{
            using namespace std::chrono;
            auto now = high_resolution_clock::now();
            auto value = std::chrono::duration_cast<microseconds>(now - m_last_check);
            return value.count() / 1000000.0;
		}

		double GetElapsedMiliseconds() const
		{
            using namespace std::chrono;
            auto now = high_resolution_clock::now();
            auto value = std::chrono::duration_cast<microseconds>(now - m_last_check);
            return value.count() / 1000.0;
		}

        void Reset()
		{
            m_last_check = std::chrono::high_resolution_clock::now();
		}

        TimerImpl()
        {}

        TimerImpl(const TimerImpl& v)
            : m_last_check(v.m_last_check)
		{}
	};

	void Timer::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == IID_ITimer) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

    Timer::Timer()
        : impl(new TimerImpl)
    {
    }

	Timer::~Timer()
	{
		delete impl;
		impl = nullptr;
	}

	double Timer::GetElapsedSeconds() const
    {
		return impl->GetElapsedSeconds();
    }

	double Timer::GetElapsedMiliseconds() const
	{
		return impl->GetElapsedMiliseconds();
	}
		
    void Timer::Reset()
    {
        impl->Reset();
    }

    double Timer::GetTime() const
    {
        return impl->GetTime();
    }

    PUNK_REGISTER_CREATOR(IID_ITimer, (System::CreateInstance<Timer, ITimer>));
}
PUNK_ENGINE_END
