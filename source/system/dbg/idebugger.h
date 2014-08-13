#ifndef _H_IDEBUGGER
#define _H_IDEBUGGER

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace System {
	
	class ISupportDebug;
	class IDebugger;

	extern "C" PUNK_ENGINE_API IDebugger* pesGetDebuggerInstance();
	extern "C" PUNK_ENGINE_API void pesDestroyDebuggerInstance();

	class IDebugger {
	public:
		virtual void TrackInstance(ISupportDebug* instance) = 0;
		virtual void UntrackInstance(ISupportDebug* instance) = 0;
		virtual std::uint32_t GetTrackInstanceCount() const = 0;
		virtual ISupportDebug* FirstTrackInstance() const = 0;
		virtual ISupportDebug* NextTrackInstance() const = 0;
		virtual void Lock() = 0;
		virtual void Unlock() = 0;

		static IDebugger* Instance() {
			return pesGetDebuggerInstance();
		}

		static void Destroy() {
			pesDestroyDebuggerInstance();
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_IDEBUGGER