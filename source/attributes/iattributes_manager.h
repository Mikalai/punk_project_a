#ifndef _H_IATTRIBUTES_MANAGER
#define _H_IATTRIBUTES_MANAGER

#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	DECLARE_PUNK_GUID(IID_IAttributesManager, "2DD3F9FE-C139-479D-BF94-2BCEB4CEC8E2");
	DECLARE_PUNK_GUID(CLSID_AttributesManager, "F850F457-3E87-4B1E-9A86-E671F6A72424");

	class IAttributesManager : public Core::IObject {
	public:		
		virtual std::uint32_t AddGroup(const Core::String& group) = 0;		
		virtual std::uint32_t GetGroupsCount() const = 0;
		virtual const Core::String GetGroupName(const std::uint32_t group_index) const = 0;
		virtual std::uint32_t GetAttributesCount(std::uint32_t group_index) const = 0;
		virtual const Core::String GetAttributeName(std::uint32_t group_index, std::uint32_t attribute_index) const = 0;
		virtual const Core::String GetAttributeDescription(std::uint32_t group_index, std::uint32_t attribute_index) const = 0;
		virtual const Core::Guid GetAttributeClsid(std::uint32_t group_index, std::uint32_t attribute_index) const = 0;
		virtual void AddAttribute(std::uint32_t group_index, const Core::Guid& clsid, const Core::String& name, const Core::String& description) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IATTRIBUTES_MANAGER