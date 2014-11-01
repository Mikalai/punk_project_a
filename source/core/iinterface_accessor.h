#ifndef _H_IINTERFACE_ACCESSOR
#define _H_IINTERFACE_ACCESSOR

#include "iobject.h"

PUNK_ENGINE_BEGIN
namespace Core {

	DECLARE_PUNK_GUID(IID_IInterfaceAccessor, "E2F7D822-E4DD-4DF2-8AA5-02E7BE3A920B");

	class IInterfaceAccessor : public IObject {
	public:
		virtual std::uint32_t GetInterfacesCount() const = 0;
		virtual const Core::Guid GetInterface(int index) const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IINTERFACE_ACCESSOR