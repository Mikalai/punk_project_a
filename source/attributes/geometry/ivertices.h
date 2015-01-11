#ifndef _H_GEOMETRY_VERTICES
#define _H_GEOMETRY_VERTICES

#include <config.h>
#include <system/factory/interface.h>
#include <attributes/data_flow/iinput.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	DECLARE_PUNK_GUID(IID_IVertices, "CDFF1E08-AF11-4D94-ACD4-CD547344FCFC");
	DECLARE_PUNK_GUID(CLSID_Vertices, "16FFAC1C-64F3-4F36-8FB8-9D38097072F8");

	class IVertices : public Core::IObject {
	public:
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void AddInput(IInputPtr value) = 0;
		virtual std::uint32_t GetInputsCount() const = 0;
		virtual IInputPtr GetInput(std::uint32_t index) const = 0;
	};

	using IVerticesPtr = Core::Pointer < IVertices > ;

	inline IVerticesPtr NewVertices() {
		return System::CreateInstancePtr<IVertices>(CLSID_Vertices, IID_IVertices);
	}
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_VERTICES