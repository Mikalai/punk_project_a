
#include <stdint.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined __gnu_linux__
#include <chrono>
#endif

#include "timer.h"
#include <system/factory/module.h>

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
            auto value = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
            double count = value.count();
            return count / 1000000.0;
        }

		double GetElapsedSeconds() const
		{
            using namespace std::chrono;
            auto now = high_resolution_clock::now();
            auto value = std::chrono::duration_cast<seconds>(now - m_last_check);
            return value.count();
		}

		double GetElapsedMiliseconds() const
		{
            using namespace std::chrono;
            auto now = high_resolution_clock::now();
            auto value = std::chrono::duration_cast<milliseconds>(now - m_last_check);
            return value.count();
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
