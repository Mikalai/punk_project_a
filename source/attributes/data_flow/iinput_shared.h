#ifndef _H_DATA_FLOW_INPUT_SHARED
#define _H_DATA_FLOW_INPUT_SHARED

#include <config.h>
#include <system/factory/interface.h>
#include "iinput.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	DECLARE_PUNK_GUID(IID_IInputShared, "7045AC32-34C2-4D63-96DB-31F774AA56E2");
	DECLARE_PUNK_GUID(CLSID_InputShared, "0CBC0383-4BE5-4A6B-956A-63F0151326DA");

	class IInputShared : public IInput {
	public:
		virtual void SetOffset(std::uint32_t value) = 0;
		virtual std::uint32_t GetOffset() const = 0;
		virtual void SetSet(std::uint32_t value) = 0;
		virtual std::uint32_t GetSet() const = 0;
	};
	
	using IInputSharedPtr = Core::Pointer < IInputShared >;

	inline IInputSharedPtr NewInputShared() {
		return System::CreateInstancePtr<IInputShared>(CLSID_InputShared, IID_IInputShared);
	}
}
PUNK_ENGINE_END

#endif	//	_H_DATA_FLOW_INPUT_SHARED