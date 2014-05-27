#ifndef _H_ITEXT_ATTRIBUTE
#define _H_ITEXT_ATTRIBUTE

#include <config.h>
#include <core/iobject.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IText, "023C889E-1706-45C1-B02A-0755C11D27DB");
	
	class IText : public virtual Core::IObject {
	public:
		virtual const Core::String GetText() const = 0;
		virtual void SetText(const Core::String& value) = 0;
	};

}
PUNK_ENGINE_END

#endif	//	_H_ITEXT_ATTRIBUTE