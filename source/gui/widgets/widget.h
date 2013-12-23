#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <core/action.h>
#include <gui/common/style.h>

PUNK_ENGINE_BEGIN
namespace Gui
{
	class ContainerWidget;
	class WidgetRender;
	class Style;

	class Widget;
    typedef Widget* WidgetPtr;

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
    class Widget
    {
    public:		
		Widget(float x, float y, float width, float height, int order, const std::string& name);
        virtual ~Widget();

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
        const AbstractPicture* GetBackTexture() const { return m_current_back_texture; }

    protected:
        void Parent(ContainerWidget* value);
        void SetBackColor(const Color& value) { m_current_back_color = value; }
        void SetFontColor(const Color& value) { m_current_font_color = value; }
        void SetBackTexture(AbstractPicture* value) { m_current_back_texture = value; }

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
        AbstractPicture* m_current_back_texture;
        AbstractPicture* m_cursor;

        friend void Attach(WidgetPtr child, ContainerWidget* parent);
        friend void Detach(WidgetPtr widget);
    };
}
PUNK_ENGINE_END

#endif // WIDGET_H
