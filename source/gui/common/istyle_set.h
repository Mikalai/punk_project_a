#ifndef _H_STYLE_SET
#define _H_STYLE_SET

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Gui {
	class IStyle;

	DECLARE_PUNK_GUID(IID_IStyleSet, "EBE1A489-D54F-4A9C-8055-495D5EAD4AA4");

	class IStyleSet :public Core::IObject {
	public:
		virtual Core::Pointer<IStyle> GetStyle(const Core::String& type) = 0;
		virtual void SetStyle(const Core::String& type, Core::Pointer<IStyle> value) = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
	};

}
PUNK_ENGINE_END
#endif	