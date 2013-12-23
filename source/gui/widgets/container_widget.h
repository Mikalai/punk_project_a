#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

#include <map>
#include <core/action.h>
#include "widget.h"

namespace Gui
{
	/**
	*	Extension of the Widget class.
	*	ContainerWidget can be used to store other widgets.
	*	To add or remove widget from container Attach and Detach methods should be used.
	*/
	class ContainerWidget : public Widget
    {
    public:		
		///	Key is a widget order. Using order as a key makes collection sorted by order.
		typedef std::multimap<int, WidgetPtr > ChildrenCollection;
	
	public:

        ContainerWidget(float x, float y, float width, float height, int order, const std::string& name);
		virtual ~ContainerWidget();        
        virtual void AddWidget(WidgetPtr w);
        virtual void RemoveWidget(WidgetPtr w);

		WidgetPtr GetWidget(float x, float y);
		ChildrenCollection& GetChildren() { return m_children; }
		const ChildrenCollection& GetChildren() const { return m_children; }

        WidgetPtr FindChildByName(const std::string& name);
        void RemoveChildByName(const std::string& name);

    protected:
        void OnRepaint(WidgetRender* render);

    private:
		ChildrenCollection m_children;
    };

    typedef boost::shared_ptr<ContainerWidget> ContainerWidgetPtr;

	void Attach(WidgetPtr child, boost::shared_ptr<ContainerWidget> parent);
	void Detach(WidgetPtr widget);
}

#endif // CONTAINER_WIDGET_H
