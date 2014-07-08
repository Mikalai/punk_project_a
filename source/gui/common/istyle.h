#ifndef _H_WIDGET_STYLE
#define _H_WIDGET_STYLE

#include <map>
#include <config.h>
#include <math/vec4.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
	class ITexture2D;
}
namespace Gui
{
	enum class StylePart { BACK_COLOR = 0, BACK_COLOR_MOUSE_OVER = 1, BACK_COLOR_FOCUSED = 2, BACK_COLOR_MOUSE_PRESSED = 3 };

	inline constexpr int GetIndex(StylePart value) { return (int)value; }

	DECLARE_PUNK_GUID(IID_IStyle, "E80DC6AB-0A4D-443C-945B-B8940583B7D0");

	/**
	*	Holds data, that influence widgets visual representation.
	*	It has a set of colors and textures for different widget states:
	*	- Default state;
	*	- Mouse over widget;
	*	- Mouse clicked widget;
	*	- Widget focused;
	*/
	class IStyle : public Core::IObject
	{
    public:
		virtual Core::Pointer<Graphics::ITexture2D> GetBackTexture(StylePart part) const = 0;
		virtual const Math::vec4& GetBackColor(StylePart part) const = 0;
		virtual void EnableTextures(bool value) = 0;
		virtual bool IsEnabledTextures() const = 0;
		virtual void SetBackColor(StylePart part, float r, float g, float b, float a) = 0;
		virtual void SetFontColor(StylePart part, float r, float g, float b, float a) = 0;
		virtual void SetBackTexture(StylePart part, Core::Pointer<Graphics::ITexture2D> value) = 0;
		virtual void SetType(const Core::String& value) = 0;
		virtual const Core::String& GetType() const = 0;
		virtual void SetFont(const Core::String& value) = 0;
		virtual const Core::String& GetFont() const = 0;		
		virtual void SetCursor(Core::Pointer<Graphics::ITexture2D> value) = 0;
		virtual const Core::Pointer<Graphics::ITexture2D> GetCursor() const = 0;
    };

    
}
PUNK_ENGINE_END

#endif
