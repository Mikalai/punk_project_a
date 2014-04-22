#include <sstream>
#include "profiler.h"

PUNK_ENGINE_BEGIN
namespace System
{
	//
	//	Implementation of profiler goes here
	//
	Profiler::Profiler()
	{
	}

	void Profiler::Start(const Core::String& description)
	{
		m_description = description;
		m_start_time = m_timer.GetElapsedSeconds();
        m_timer.Reset();
	}

    double Profiler::End()
	{
		return m_end_time = m_timer.GetElapsedSeconds();
	}

	double Profiler::ToMiliseconds() const
	{
        return (m_end_time - m_start_time) * 1000.0f;
	}

	const Core::String Profiler::ToString() const
	{
		std::wstringstream stream;
        stream << m_description.Data() << L": " << ToMiliseconds() << L" ms; ";
		return Core::String(stream.str().c_str());
	}
}
PUNK_ENGINE_END
