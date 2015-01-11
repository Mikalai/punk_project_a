#ifndef _H_GEOMETRY_VERTEX_COUNT
#define _H_GEOMETRY_VERTEX_COUNT

#include <config.h>
#include <system/factory/interface.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IVertexCountList, "65D81C25-5DD4-4050-8189-3BD9650F2FF3");
	DECLARE_PUNK_GUID(CLSID_VertexCountList, "F9315ECB-5A62-4E97-A2EB-BDA6458E021E");

	class IVertexCountList : public Core::IObject {
	public:
		virtual std::uint32_t GetSize() const = 0;
		virtual void SetSize(std::uint32_t value) = 0;
		virtual std::uint32_t GetValue(std::uint32_t index) = 0;
		virtual void AddValue(std::uint32_t value) = 0;
	};

	using IVertexCountListPtr = Core::Pointer < IVertexCountList >;

	inline IVertexCountListPtr NewVertexCountList() {
		return System::CreateInstancePtr<IVertexCountList>(CLSID_VertexCountList, IID_IVertexCountList);
	}
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_VERTEX_COUNT