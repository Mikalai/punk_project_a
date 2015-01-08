#ifndef _H_IPARAM
#define _H_IPARAM

#include <config.h>
#include <system/factory/interface.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IParam, "446F97AE-F5F5-47A2-8DCA-83383FAE047B");
	DECLARE_PUNK_GUID(CLSID_Param, "05C322C4-2256-4AB1-8739-4107501D4404");

	enum class ParamType {
		Bad,
		Int,
		Float
	};

	enum class ParamSemantic {
		Bad
	};

	template<typename Type> struct ParamTypeAccessor;
	
	template<> struct ParamTypeAccessor<float> {
		static const ParamType Value = ParamType::Float;
	};

	template<> struct ParamTypeAccessor<int> {
		static const ParamType Value = ParamType::Int;
	};

	class IParam : public Core::IObject {
	public:
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetSid(const Core::String& value) = 0;
		virtual const Core::String& GetSid() const = 0;
		virtual void SetType(ParamType value) = 0;
		virtual ParamType GetType() const = 0;
		virtual void SetSemantic(ParamSemantic value) = 0;
		virtual ParamSemantic GetSemantic() const = 0;
	};

	using IParamPtr = Core::Pointer < IParam > ;

	inline IParamPtr NewParam() {
		return System::CreateInstancePtr<IParam>(CLSID_Param, IID_IParam);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IPARAM