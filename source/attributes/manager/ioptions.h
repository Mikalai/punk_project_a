#ifndef _H_ATTRIBUTES_IOPTIONS
#define _H_ATTRIBUTES_IOPTIONS

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Attributes {
	DECLARE_PUNK_GUID(IID_IOptions, "44D72862-79C6-40E5-ACE1-48920ECFB055");

	class IOptions : public Core::IObject {
	public:
		virtual const Core::String& GetDataPath() const = 0;
		virtual void SetDataPath(const Core::String& value) = 0;
	};
}
PUNK_ENGINE_END

#endif
