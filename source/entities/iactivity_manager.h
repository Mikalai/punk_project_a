#ifndef _H_IACTIVITY_MANAGER
#define _H_IACTIVITY_MANAGER

#include <config.h>
#include <core/iobject.h>
#include <core/action.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	class IActivityManager;

	extern "C" PUNK_ENGINE_API IActivityManager* GetActivityManagerInstance();
	extern "C" PUNK_ENGINE_API void DestroyActivityManagerInstance();

	class IActivityManager : public Core::IObject {
	public:

		virtual void DispatchActivity(Core::Pointer<IActivity> value) = 0;
		virtual void AddActivityConsumer(Core::Poinetr<Core::ActionBase<Core::Pointer<IActivity>>> consumer) = 0;

		static IActivityManager* Instance() {
			return GetActivityManagerInstance();
		}

		static void Destroy() {
			DestroyActivityManagerInstance();
		}
	};	
}
PUNK_ENGINE_END

#endif	//	_H_IACTIVITY_MANAGER