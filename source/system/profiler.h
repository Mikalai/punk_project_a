#ifndef _H_PUNK_SYSTE_PROFILER
#define _H_PUNK_SYSTE_PROFILER

#include <config.h>
#include <string/string.h>
#include <system/time/timer.h>

PUNK_ENGINE_BEGIN
namespace System
{
	/*
	*	Used to measure small pieces of time
	*/
	class PUNK_ENGINE_LOCAL Profiler
	{
		//	High definition timer
		Timer m_timer;		
		// Text descritpion of current profiler
		Core::String m_description;
        double m_start_time;
        double m_end_time;
		// No copy
		Profiler(const Profiler&);
		// No copy
		Profiler& operator = (const Profiler&);
	public:
		Profiler();
		/*
		*	Start profiler and assigns new description to it
		*	@param description Textual representation of the profiler
		*/
		void Start(const Core::String& description);
		/*
		*	Stops profiling
		*	@returns Tick count elapsed from start
		*/
        double End();
		/*
		*	Converts ticks to milliseconds
		*	@return Elapsed time ib milliseconds
		*/
		double ToMiliseconds() const;
		/*
		*	Returns nice textual representation of the profiling result
		*/
		const Core::String ToString() const;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTE_PROFILER
