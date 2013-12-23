#include <core/action.h>
#include <gui/common/widget_render.h>
#include <gui/common/style.h>
#include "button.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
    Button::Button(float x, float y, float width, float height, int order, const std::string& text, const std::string& name)
        : Widget(x, y, width, height, order, name)
		, m_checkable(false)
		, m_checked(false)
    {
        SetText(text);
        SetMoveable(false);
        SetFixed(true);
    }

	void Button::OnRepaint(WidgetRender *r)
    {
        if (!IsVisible())
			return;
		r->Render(this);        
    }   

    void Button::Checkable(bool value)
    {
        m_checkable = value;
    }

    bool Button::Checkable() const
    {
        return m_checkable;
    }

    void Button::Checked(bool value)
    {
        m_checked = value;
    }

    bool Button::Checked() const
    {
        return m_checked;
    }

	void Button::OnMousePress(float x, float y, int button)
	{
        boost::shared_ptr<Gui::Style> style = GetStyle();
        SetBackColor(style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_PRESSED));
        SetBackTexture(style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_PRESSED));
        m_checked = true;
	}

	void Button::OnMouseRelease(float x, float y, int button)
	{
        boost::shared_ptr<Gui::Style> style = GetStyle();
		if (IsFocused())
        {
            SetBackColor(style->GetBackColor(Gui::Style::BACK_COLOR_FOCUSED));
            SetBackTexture(style->GetBackTexture(Gui::Style::BACK_COLOR_FOCUSED));
        }
		else if (IsMouseOver())
        {
            SetBackColor(style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER));
            SetBackTexture(style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_OVER));
        }
		else 
        {
            SetBackColor(style->GetBackColor(Gui::Style::BACK_COLOR));
            SetBackTexture(style->GetBackTexture(Gui::Style::BACK_COLOR));
        }
        m_checked = false;

        Toggle();
	}

    void Button::SetStyle(boost::shared_ptr<Gui::Style> value)
    {
        Widget::SetStyle(value);
        Gui::Style* style = GetStyle().get();
        if (m_checked)
        {
            SetBackColor(style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_PRESSED));
            SetBackTexture(style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_PRESSED));
        }
    }
}
PUNK_ENGINE_END

