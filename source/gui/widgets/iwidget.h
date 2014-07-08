#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <attributes/selection/imouse_selectable2d.h>
#include <core/action.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Gui
{
	class IContainerWidget;
	class IWidgetRender;
	class IStyle;

	class IWidget;
	
	using ResizeAction = Core::Pointer < Core::ActionBase < float, float, float, float > > ;
	using VisibilityChangedAction = Core::Pointer < Core::ActionBase < bool > >; 
	
	DECLARE_PUNK_GUID(IID_IWidget, "A697B349-1851-44E4-9AE0-7343B0891019");

	class IWidget : public Attributes::IMouseSelectable2D
	{
	public:				
		virtual void SubscribeOnResize(ResizeAction value) = 0;
		virtual void SubscribeOnVisibilityChanged(VisibilityChangedAction value) = 0;
		virtual void SetWidth(float value) = 0;
		virtual void SetHeight(float value) = 0;
		virtual float GetGlobalX() const = 0;
		virtual float GetGlobalY() const = 0;
		virtual void SetLocalX(float value) = 0;
		virtual void SetLocalY(float value) = 0;		
		virtual void SetLocalPosition(float x, float y) = 0;
		virtual Core::String& GetName() const = 0;
		virtual void Invalidate() = 0;
		virtual IWidget* GetWidget(float x, float y) = 0;
		virtual void SetMoveable(bool value) = 0;
		virtual bool IsMoveable() const = 0;
		virtual void SetVisible(bool value) = 0;
		virtual bool IsVisible() const = 0;
		virtual void SwitchVisibility() = 0;
		virtual void SetFixed(bool value) = 0;
		virtual bool IsFixed() const = 0;
		virtual int GetOrder() const = 0;
		virtual void SetOrder(int value) = 0;
		virtual IStyle* GetStyle() = 0;
		virtual void SetStyle(IStyle* value) = 0;
		virtual IContainerWidget* Parent() const = 0;
		
		virtual void EmitResize(float x, float y, float width, float height) = 0;
		virtual void Repaint(IWidgetRender* r) = 0;
		virtual void Update(float dt) = 0;		
		virtual bool IsFocused() const = 0;
		virtual bool IsMouseOver() const = 0;

		virtual const Color& GetBackColor() const = 0;
		virtual const Color& GetFontColor() const = 0;
		virtual const Graphics::ITexture2D* GetBackTexture() const = 0;

		virtual void SetParent(IContainerWidget* value) = 0;
		virtual IContainerWidget* GetParent() const = 0;
		virtual void SetBackColor(const Color& value) = 0;
		virtual void SetFontColor(const Color& value) = 0;
		virtual void SetBackTexture(Graphics::ITexture2D* value) = 0;
		virtual void OnMouseMove(float x, float y, int button);
		virtual void OnMousePress(float x, float y, int button);
		virtual void OnMouseRelease(float x, float y, int button);
		virtual void OnClicked(float x, float y, int button);
		virtual void OnMouseEnter(float x, float y);
		virtual void OnMouseLeave(float x, float y);
		virtual void OnFocused();
		virtual void OnUnfocused();
		virtual void OnRepaint(IWidgetRender* r);
		virtual void OnUpdate(float dt);
		virtual void OnResize(float x, float y, float width, float height);
	};
}
PUNK_ENGINE_END

#endif // WIDGET_H
