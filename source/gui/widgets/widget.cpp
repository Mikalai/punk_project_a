#include <string>
#include <stdexcept>
#include <algorithm>
#include <gui/common/widget_render.h>
#include <gui/common/style.h>
#include "container_widget.h"
#include "widget.h"
#include "manager.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
	Widget::Widget(float x, float y, float width, float height, int order, const std::string& name)
        : m_style(new Gui::Style)
        , m_name(name)
		, m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_fixed(true)
        , m_mouse_over(false)
        , m_moveable(false)
        , m_visible(false)		
        , m_focused(false)		        
        , m_order(order)
    {
    }

    Widget::~Widget()
    {
    }

    float Widget::GetWidth() const
    {
        return m_width;
    }

    float Widget::GetHeight() const
    {
        return m_height;
    }

    void Widget::GetWidth(float value)
    {
        Resize(m_x, m_y, value, m_height);
    }

    void Widget::SetHeight(float value)
    {        
        Resize(m_x, m_y, m_width, value);
    }

    float Widget::GetLocalX() const
    {
        return m_x;
    }

    float Widget::GetLocalY() const
    {
        return m_y;
    }

    void Widget::SetLocalX(float value)
    {        
        Resize(value, m_y, m_width, m_height);
    }

    void Widget::SetLocalY(float value)
    {        
        Resize(m_x, value, m_width, m_height);
    }

    float Widget::GetGlobalX() const
    {
		boost::shared_ptr<ContainerWidget> parent = m_parent.lock();
        if (parent.get())
            return parent->GetGlobalX() + m_x;
        return m_x;
    }

    float Widget::GetGlobalY() const
    {
		boost::shared_ptr<ContainerWidget> parent = m_parent.lock();
		if (parent.get())
            return parent->GetGlobalY() + m_y;
        return m_y;
    }

    /// Set position relative to parent.
    void Widget::SetLocalPosition(float x, float y)
    {
        ContainerWidget* parent = m_parent.lock();
		float w = (parent.get() ? parent->GetWidth() : Manager::Instance()->GetWindowWidth()) - m_width;
        float h = (parent.get() ? parent->GetHeight() : Manager::Instance()->GetWindowHeight()) - m_height;
        x = std::min(std::max((float)x, 0.0f), w);
        y = std::min(std::max((float)y, 0.0f), h);
        Resize(x, y, m_width, m_height);
    }     

    void Widget::OnMouseMove(float x, float y, int button)
    {

    }

    void Widget::OnMousePress(float x, float y, int button)
    {

    }

    void Widget::OnMouseRelease(float x, float y, int button)
    {
    }

    void Widget::OnResize(float xx, float yy, float width, float height)
    {
        m_width = width;
        m_height = height;
        m_x = xx;
        m_y = yy;
    }

    void Widget::OnMouseEnter(float x, float y)
    {
        if (m_focused)
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_FOCUSED));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_FOCUSED));
        }
        else
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_OVER));
        }
    }

    void Widget::OnMouseLeave(float x, float y)
    {
        if (m_focused)
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_FOCUSED));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_FOCUSED));
        }
        else
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR));
        }
    }

    void Widget::OnFocused()
    {
        SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_FOCUSED));
        SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_FOCUSED));
    }

    void Widget::OnUnfocused()
    {
        if (m_mouse_over)
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_OVER));
        }
        else
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR));
        }
    }

	void Widget::OnRepaint(WidgetRender* r)
    {
        if (!IsVisible())
            return;
		r->Render(this);        
    }

    void Widget::OnUpdate(float dt)
    {
    }

    void Widget::OnClicked(float x, float y, int button)
    {
	}

	void Widget::MouseMove(float x, float y, int button)
    {
		MouseMoved(x, y, button);
        OnMouseMove(x, y, button);
    }

	void Widget::MousePress(float x, float y, int key)
    {
		MousePressed(x, y, key);
        OnMousePress(x, y, key);
    }

    void Widget::MouseRelease(float x, float y, int key)
    {
		MouseReleased(x, y, key);
        OnMouseRelease(x, y, key);
    }

    void Widget::MouseEnter(float x, float y)
    {
        m_mouse_over = true;
		MouseEntered(x, y, this);
        MouseEnteredNotify();
        OnMouseEnter(x, y);
    }

    void Widget::MouseLeave(float x, float y)
    {
        m_mouse_over = false;        
		MouseLeaved(x, y, this);
        MouseLeavedNotify();
        OnMouseLeave(x, y);
    }

	void Widget::Focus()
    {
		m_focused = true;
        Focused(true);        
        OnFocused();
    }

	void Widget::Repaint(WidgetRender *r)
    {
        OnRepaint(r);
    }

    void Widget::Update(float dt)
    {
        OnUpdate(dt);
    }

    void Widget::Unfocus()
    {
        m_focused = false;
        Focused(false);
        OnUnfocused();
    }

    void Widget::Resize(float x, float y, float width, float height)
    {
        if (x == m_x && y == m_y && m_width == width && m_height == height)
            return;

		Resized(x, y, width, height);
        OnResize(x, y, width, height);
    }

    bool Widget::IsFocused() const
    {        
        return m_focused;
    }

    bool Widget::IsMouseOver() const
    {
        return m_mouse_over;
    }

	void Widget::MouseClick(float x, float y, int button)
    {        
		MouseClicked(x, y, button);
        OnClicked(x, y, button);
	}

    void Widget::SetStyle(boost::shared_ptr<Gui::Style> value)
    {
        m_style = value;
        if (m_focused)
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_FOCUSED));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_FOCUSED));
        }
        else if (m_mouse_over)
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR_MOUSE_OVER));
        }
        else
        {
            SetBackColor(m_style->GetBackColor(Gui::Style::BACK_COLOR));
            SetBackTexture(m_style->GetBackTexture(Gui::Style::BACK_COLOR));
        }
    }

    void Widget::Parent(boost::weak_ptr<ContainerWidget> value)
    {
        m_parent = value;
    }

    void Widget::SetOrder(int value)
    {
        boost::shared_ptr<ContainerWidget> parent = m_parent.lock();
        if (!parent.get())
        {
            m_order = value;
            return;
        }

        WidgetPtr _this = parent->FindChildByName(m_name);
        if (_this.get() != this)
            throw std::runtime_error("Doublicate name detected" + m_name);

        Detach(_this);
        m_order = value;
        Attach(_this, parent);
    }
}
PUNK_ENGINE_END

