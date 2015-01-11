#ifndef _H_GEOMETRY_PRIMITIVE_LIST
#define _H_GEOMETRY_PRIMITIVE_LIST

#include <config.h>
#include <system/factory/interface.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IPrimitivesList, "3701C5B7-76B3-422D-909E-0FC9970C09EF");
	DECLARE_PUNK_GUID(CLSID_PrimitivesList, "BEE560B4-EC39-4274-AB1E-6C9293595C56");

	class IPrimitivesList : public Core::IObject {
	public:
		virtual std::uint32_t GetSize() const = 0;
		virtual void SetSize(std::uint32_t value) = 0;
		virtual std::uint32_t GetValue(std::uint32_t index) = 0;
		virtual void AddValue(std::uint32_t value) = 0;
	};

	using IPrimitivesListPtr = Core::Pointer < IPrimitivesList >;

	inline IPrimitivesListPtr NewPrimitivesList() {
		return System::CreateInstancePtr<IPrimitivesList>(CLSID_PrimitivesList, IID_IPrimitivesList);
	}
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_PRIMITIVE_LIST