//#ifndef CONTAINER_WIDGET_H
//#define CONTAINER_WIDGET_H
//
//#include <config.h>
//#include <map>
//#include <core/action.h>
//#include "iwidget.h"
//
//PUNK_ENGINE_BEGIN
//namespace Gui
//{
//	/**
//	*	Extension of the Widget class.
//	*	ContainerWidget can be used to store other widgets.
//	*	To add or remove widget from container Attach and Detach methods should be used.
//	*/
//	class IContainerWidget : public IWidget
//    {
//	public:						
//		const ChildrenCollection& GetChildren() const { return m_children; }
//
//        WidgetPtr FindChildByName(const std::string& name);
//        void RemoveChildByName(const std::string& name);
//
//    protected:
//        void OnRepaint(WidgetRender* render);
//
//    private:
//		ChildrenCollection m_children;
//    };
//
//    typedef boost::shared_ptr<ContainerWidget> ContainerWidgetPtr;
//
//	void Attach(WidgetPtr child, boost::shared_ptr<ContainerWidget> parent);
//	void Detach(WidgetPtr widget);
//}
//PUNK_ENGINE_END
//
//#endif // CONTAINER_WIDGET_H
