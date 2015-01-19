#ifndef _H_GEOMETRY_POLYLIST
#define _H_GEOMETRY_POLYLIST

#include <config.h>
#include <system/factory/interface.h>
#include <attributes/data_flow/iinput_shared.h>
#include "ivertex_count_list.h"
#include "iprimitive_list.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IPolyList, "D40514C7-DB2A-486B-9F56-B1D49C0B80B2");
	DECLARE_PUNK_GUID(CLSID_PolyList, "5CC7805F-A93E-4C0A-A02F-40E910524698");

	class IPolyList : public Core::IObject {
	public:
		virtual void SetSize(std::uint32_t value) = 0;
		virtual std::uint32_t GetSize() const = 0;
		virtual void SetMaterialRef(const Core::String& value) = 0;
		virtual const Core::String GetMaterialRef() const = 0;
		virtual void SetVertexCountList(IVertexCountListPtr value) = 0;
		virtual const IVertexCountListPtr GetVertexCountList() const = 0;		
		virtual void AddInput(IInputSharedPtr value) = 0;
		virtual std::uint32_t GetInputsCount() const = 0;
		virtual IInputSharedPtr GetInput(std::uint32_t value) = 0;
		virtual void SetPrimitivesList(IPrimitivesListPtr value) = 0;
		virtual IPrimitivesListPtr GetPrimitivesList() const = 0;
	};

	using IPolyListPtr = Core::Pointer < IPolyList>;

	inline IPolyListPtr NewPolyList() {
		return System::CreateInstancePtr<IPolyList>(CLSID_PolyList, IID_IPolyList);
	}
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_POLYLIST
