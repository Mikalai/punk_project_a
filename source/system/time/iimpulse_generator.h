#ifndef _H_IMPULSE_GENERATOR
#define _H_IMPULSE_GENERATOR

#include <config.h>
#include <core/iobject.h>
#include <core/action.h>

PUNK_ENGINE_BEGIN
namespace System {

	class IImpulseGenerator;

	extern "C" PUNK_ENGINE_API IImpulseGenerator* GetImpulseGeneratorInstance();
	extern "C" PUNK_ENGINE_API void DestroyImpulseGeneratorInstance();

	DECLARE_PUNK_GUID(IID_IImpulseGenerator, "39FBE3DB-F9EF-4504-B113-0F6A06EBE47B");

	using ImpulsedAction = Core::Pointer < Core::ActionBase<std::uint32_t> > ;

	class IImpulseGenerator : public Core::IObject {
	public:
		virtual void SetPeriod(std::uint32_t milliseconds) = 0;
		virtual std::uint32_t GetPeriod() = 0;
		virtual void AddAction(std::uint32_t multiplier, ImpulsedAction action, bool repeat) = 0;
		virtual void RemoveAction(ImpulsedAction action) = 0;

		static Core::Pointer<IImpulseGenerator> Instance() {
			auto result = Core::Pointer < IImpulseGenerator > {GetImpulseGeneratorInstance(), Core::DestroyObject};
			return result;
		}

		static void Destroy() {
			DestroyImpulseGeneratorInstance();
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_IMPULSE_GENERATOR