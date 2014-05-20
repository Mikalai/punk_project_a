#ifndef _H_IPROCESSOR
#define _H_IPROCESSOR

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class CommandBase;

	class IProcessor {
	public:
		virtual void OnInitialize() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnStartProcessing() = 0;
		virtual void OnIdle(int dt) = 0;
		virtual void OnInternalUpdate(CommandBase* task) = 0;
		virtual void OnPreUpdate(CommandBase* command) = 0;
		virtual void OnPostUpdate(CommandBase* command) = 0;
		virtual void OnWaitProcessingComplete() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IPROCESSOR