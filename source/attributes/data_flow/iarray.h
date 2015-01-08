#ifndef _H_IARRAY
#define _H_IARRAY

#include <config.h>
#include <core/iobject.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IArray, "53A411B6-0367-4576-8764-9D6EC74425FF");

	class IArray : public Core::IObject {
	public:
		virtual std::uint32_t GetCount() const = 0;
		virtual void SetCount(std::uint32_t value) = 0;
		virtual const Core::String GetId() = 0;
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetName() = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual void* Data() = 0;
		virtual const void* Data() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IARRAY