#include <string>
#include <stdexcept>
#include <algorithm>
#include <core/iobject_impl.h>
#include <system/factory/module.h>
#include <gui/common/widget_render.h>
#include <gui/common/istyle.h>
#include "icontainer_widget.h"
#include "iwidget.h"
#include "manager.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
	class IStyle;

	/**
	*	Base class for all gui elements.
	*	Widget can be moveable, visible, fixed (not implemented).
	*	When some interaction arrive (mouse events, focus, unfocus) corresponding slot will be activated. Some events can
	*	activate several slots.
	*	Widget visual style is defined by assigned Style object.
	*	During construction unique name should be provided. User is responsible to provide unique name for the time present.
	*	It has a set of virtual methods that could be overriden by inherited gui elements.
	*	Widget visualization is performed by WidgetRender (Visitor pattern is used).
	*	To make widget to be a part of any container widget explicit methods Attach and Detach are defined.
	*	Position of the widget is specified in the local space of parent widget.
	*/
	class Widget : public IWidget
	{
	public:
		Widget(float x, float y, float width, float height, int order, const std::string& name);
		virtual ~Widget();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, Attributes::IID_IMouseSelectable2D, IID_IWidget });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		float GetLocalTopLeftX() const override {
			m_
		}

		virtual float GetLocalTopLeftY() const = 0;
		virtual const Math::vec2 GetLocalTopLeftPosition() const = 0;
		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;

		Core::ActionSlot<float, float, int> MouseMoved;
		Core::ActionSlot<float, float, int> MousePressed;
		Core::ActionSlot<float, float, int> MouseReleased;
		Core::ActionSlot<float, float, Widget*> MouseEntered;
		Core::ActionSlot<void> MouseEnteredNotify;
		Core::ActionSlot<float, float, Widget*> MouseLeaved;
		Core::ActionSlot<void> MouseLeavedNotify;
		Core::ActionSlot<float, float, float, float> Resized;
		Core::ActionSlot<bool> VisibilityChanged;
		Core::ActionSlot<float, float, int> MouseClicked;
		Core::ActionSlot<bool> Focused;

		float GetWidth() const;
		float GetHeight() const;
		void GetWidth(float value);
		void SetHeight(float value);

		float GetLocalX() const;
		float GetLocalY() const;
		float GetGlobalX() const;
		float GetGlobalY() const;
		void SetLocalX(float value);
		void SetLocalY(float value);
		/// Set position relative to parent.
		void SetLocalPosition(float x, float y);

		const std::string& GetName() const { return m_name; }
		void Invalidate();

		/// x and y in the current widget coordinate system
		Widget* GetWidget(float x, float y);

		void SetMoveable(bool value) { m_moveable = value; }
		bool IsMoveable() const { return m_moveable; }
		void SetVisible(bool value) { m_visible = value; }
		bool IsVisible() const { return m_visible; }
		void SwitchVisibility() { m_visible = !m_visible; }
		void SetFixed(bool value) { m_fixed = value; }
		bool IsFixed() const { return m_fixed; }

		int GetOrder() const { return m_order; }
		void SetOrder(int value);
		Gui::Style* GetStyle() { return m_style; }
		virtual void SetStyle(Gui::Style* value);

		ContainerWidget* Parent() const { return m_parent; }

		void MouseMove(float x, float y, int button);
		void MousePress(float x, float y, int key);
		void MouseRelease(float x, float y, int key);
		void MouseEnter(float x, float y);
		void MouseLeave(float x, float y);
		void MouseClick(float x, float y, int button);
		void Focus();
		void Unfocus();
		void Repaint(WidgetRender* r);
		void Update(float dt);
		void Resize(float x, float y, float width, float height);
		bool IsFocused() const;
		bool IsMouseOver() const;

		const Color& GetBackColor() const { return m_current_back_color; }
		const Color& GetFontColor() const { return m_current_font_color; }
		const Graphics::ITexture2D* GetBackTexture() const { return m_current_back_texture; }

	protected:
		void Parent(ContainerWidget* value);
		void SetBackColor(const Color& value) { m_current_back_color = value; }
		void SetFontColor(const Color& value) { m_current_font_color = value; }
		void SetBackTexture(Graphics::ITexture2D* value) { m_current_back_texture = value; }

		virtual void OnMouseMove(float x, float y, int button);
		virtual void OnMousePress(float x, float y, int button);
		virtual void OnMouseRelease(float x, float y, int button);
		virtual void OnClicked(float x, float y, int button);
		virtual void OnMouseEnter(float x, float y);
		virtual void OnMouseLeave(float x, float y);
		virtual void OnFocused();
		virtual void OnUnfocused();
		virtual void OnRepaint(WidgetRender* r);
		virtual void OnUpdate(float dt);
		virtual void OnResize(float x, float y, float width, float height);

	private:
		ContainerWidget* m_parent;
		Gui::Style* m_style;
		std::string m_name;
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		bool m_fixed;
		bool m_mouse_over;
		bool m_moveable;
		bool m_visible;
		bool m_focused;
		int m_order;
		Color m_current_back_color;
		Color m_current_font_color;
		Graphics::ITexture2D* m_current_back_texture;
		Graphics::ITexture2D* m_cursor;

		friend void Attach(WidgetPtr child, ContainerWidget* parent);
		friend void Detach(WidgetPtr widget);
	};
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

