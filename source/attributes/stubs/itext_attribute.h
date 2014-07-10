#ifndef _H_ITEXT_ATTRIBUTE
#define _H_ITEXT_ATTRIBUTE

#include <config.h>
#include <core/iobject.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IText, "023C889E-1706-45C1-B02A-0755C11D27DB");
	DECLARE_PUNK_GUID(CLSID_Text, "0371826A-5E9E-48FB-8013-93B0ABBB2E09");
	
	class IText : public Core::IObject {
	public:
		virtual const Core::String GetText() const = 0;
		virtual void SetText(const Core::String& value) = 0;
	};

}
PUNK_ENGINE_END

#endif	//	_H_ITEXT_ATTRIBUTE