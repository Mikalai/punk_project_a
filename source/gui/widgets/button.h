#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Gui
{	
    class Style;

	/**
	*	Button is used to provide user an element that can be used as a trigger for some actions.
	*	When button is clicked Toggle slot is activated.
	*	Button is considered to be clicked if mouse was pressed and released on the same button.
	*/
    class Button : public Widget
    {
    public:
        Button(float x, float y, float width, float height, int order, const std::string& text, const std::string& name);

        Core::ActionSlot<void> Toggle;

        virtual void SetStyle(Gui::Style* value);

        void Checkable(bool value);
        bool Checkable() const;

        void Checked(bool value);
        bool Checked() const;

        void SetText(const Core::String& value) { m_text = value; }
        const Core::String& GetText() const { return m_text; }

    protected:
		virtual void OnRepaint(WidgetRender* r);
		virtual void OnMousePress(float x, float y, int button);
		virtual void OnMouseRelease(float x, float y, int button);

	private:
        bool m_checkable;
        bool m_checked;
        Core::String m_text;
    };

    typedef Button* ButtonPtr;
}
PUNK_ENGINE_END

#endif // BUTTON_H
