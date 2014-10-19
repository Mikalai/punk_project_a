#ifndef H_IJUDGMENT
#define H_IJUDGMENT

#include <config.h>
#include <core/iobject.h>
#include <core/pointer.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	class IJudgment : public Core::IObject {
	public:
		
		/**
		*	When some activity happens we can track which character performed
		*	some action. 
		*/
		virtual Core::Pointer<Core::IObject> GetExecutor() const = 0;

		/**
		*	Give rewards to the executor. To perform rewards we must have access to
		*	the authority of the fraction which claimed the law. This can be triggered when
		*	character interacts with authority. Interaction can be something like a dialog
		*	by radio or directly. If reward something not material for example respect it can
		*	be applied without any conditions, but if reward is some item than to give it 
		*	executor and authority should be nearby.
		*/
		virtual bool ApplyReward(Core::Pointer<Core::IObject> authority) = 0;

		/**
		*	Judgment can be imposed only once by one executor
		*/
		virtual bool IsImposed() = 0;

		/**
		*	Imposed should be triggered to store executor of the judgment thus later executor can
		*	be rewarded.
		*/
		virtual void Impose(Core::Pointer<Core::IObject> executor) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	H_IJUDGMENT