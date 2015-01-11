#ifndef _H_DATA_FLOW_INPUT
#define _H_DATA_FLOW_INPUT

#include <config.h>
#include <system/factory/interface.h>
#include "isource.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	enum class InputSemantic {
		Bad,
		Position,
		Vertex,
		Normal
	};

	DECLARE_PUNK_GUID(IID_IInput, "4CEDBE0A-03CE-4FF1-B023-6AB7287526A0");
	DECLARE_PUNK_GUID(CLSID_Input, "B5493446-1D17-446E-947F-1078BFB65496");

	class IInput : public Core::IObject {
	public:
		virtual void SetSemantic(InputSemantic value) = 0;
		virtual InputSemantic GetSemantic() const = 0;
		virtual void SetSourceRef(const Core::String& value) = 0;
		virtual const Core::String GetSourceRef() const = 0;
		virtual void SetSource(ISourcePtr value) = 0;
		virtual ISourcePtr GetSource() = 0;
		virtual const ISourcePtr GetSource() const = 0;
	};

	using IInputPtr = Core::Pointer < IInput > ;

	inline IInputPtr NewInput() {
		return System::CreateInstancePtr<IInput>(CLSID_Input, IID_IInput);
	}
}
PUNK_ENGINE_END

#endif	//	_H_DATA_FLOW_INPUT