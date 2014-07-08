//#include <stdexcept>
//#include <string>
//#include "container_widget.h"
//#include "../common/style.h"
//#include "../common/widget_render.h"
//#include "widget.h"
//
//PUNK_ENGINE_BEGIN
//namespace Gui
//{
//#ifndef CONTAINER_WIDGET_H
//#define CONTAINER_WIDGET_H
//
//#include <config.h>
//#include <map>
//#include <core/action.h>
//#include "iwidget.h"
//
//	punk
//	namespace Gui
//	{
//		/**
//		*	Extension of the Widget class.
//		*	ContainerWidget can be used to store other widgets.
//		*	To add or remove widget from container Attach and Detach methods should be used.
//		*/
//		class IContainerWidget : public IWidget
//		{
//		public:
//			///	Key is a widget order. Using order as a key makes collection sorted by order.
//			typedef std::multimap<int, WidgetPtr > ChildrenCollection;
//
//		public:
//
//			ContainerWidget(float x, float y, float width, float height, int order, const std::string& name);
//			virtual ~ContainerWidget();
//			virtual void AddWidget(WidgetPtr w);
//			virtual void RemoveWidget(WidgetPtr w);
//
//			WidgetPtr GetWidget(float x, float y);
//			ChildrenCollection& GetChildren() { return m_children; }
//			const ChildrenCollection& GetChildren() const { return m_children; }
//
//			WidgetPtr FindChildByName(const std::string& name);
//			void RemoveChildByName(const std::string& name);
//
//		protected:
//			void OnRepaint(WidgetRender* render);
//
//		private:
//			ChildrenCollection m_children;
//		};
//
//		typedef boost::shared_ptr<ContainerWidget> ContainerWidgetPtr;
//
//		void Attach(WidgetPtr child, boost::shared_ptr<ContainerWidget> parent);
//		void Detach(WidgetPtr widget);
//	}
//
//#endif // CONTAINER_WIDGET_H
//
//
//    ContainerWidget::ContainerWidget(float x, float y, float width, float height, int order, const std::string& name)
//        : Widget(x, y, width, height, order, name)
//    {
//        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR, 0.3, 0.3, 0.3, 0.4);
//        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER, 0.3, 0.3, 0.3, 0.5);
//        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_FOCUSED, 0.3, 0.3, 0.3, 0.9);
//        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_MOUSE_PRESSED, 0.3, 0.3, 0.3, 1.0);
//    }
//
//    ContainerWidget::~ContainerWidget()
//    {}
//
//	WidgetPtr ContainerWidget::GetWidget(float x, float y)
//	{
//		WidgetPtr res;
//
//		for (ChildrenCollection::iterator it = m_children.begin(); it != m_children.end(); ++it)
//		{
//			WidgetPtr child = (*it).second;
//            if (child->IsVisible())
//			{
//                if (x < child->GetLocalX() || x > child->GetLocalX() + child->GetWidth())
//					continue;
//                if (y < child->GetLocalY() || y > child->GetLocalY() + child->GetHeight())
//					continue;		
//
//				boost::shared_ptr<ContainerWidget> child_container(boost::dynamic_pointer_cast<ContainerWidget, Widget>(child));
//				if (child_container.get())
//				{
//                    res = child_container->GetWidget(x - child->GetLocalX(), y - child->GetLocalY());
//					if (res.get())
//						return res;
//				}
//
//				res = child;
//			}
//		}
//		return res;
//	}
//
//    void ContainerWidget::AddWidget(WidgetPtr value)
//	{
//        ChildrenCollection::iterator low = m_children.lower_bound(value->GetOrder());
//        ChildrenCollection::iterator up = m_children.upper_bound(value->GetOrder());
//		ChildrenCollection::iterator it = low;
//		
//		for (; it != low; ++it)
//		{
//			if ((*it).second.get() == value.get())
//				return;
//		}
//		
//        m_children.insert(std::make_pair<int, WidgetPtr >(value->GetOrder(), value));
//	}
//
//	void ContainerWidget::RemoveWidget(WidgetPtr value)
//	{
//        ChildrenCollection::iterator low = m_children.lower_bound(value->GetOrder());
//        ChildrenCollection::iterator up = m_children.upper_bound(value->GetOrder());
//
//		if (low == m_children.end())
//			return;
//
//		ChildrenCollection::iterator it;
//		for (it = low; it != up; ++it)
//		{
//			if ((*it).second.get() == value.get())
//				break;
//		}
//
//		if (it == m_children.end())
//			return;
//		m_children.erase(it);
//	}
//
//	void Attach(WidgetPtr child, boost::shared_ptr<ContainerWidget> parent)
//	{
//		if (child->Parent().lock().get())
//			Detach(child);
//		parent->AddWidget(child);
//		child->Parent(parent);
//	}
//
//	void Detach(WidgetPtr widget)
//	{
//		boost::shared_ptr<ContainerWidget> parent = widget->Parent().lock();
//		if (!parent.get())
//			return;
//		parent->RemoveWidget(widget);
//	}
//
//    void ContainerWidget::OnRepaint(WidgetRender *r)
//    {
//        if (!IsVisible())
//            return;
//        r->Render(this);
//    }
//
//    WidgetPtr ContainerWidget::FindChildByName(const std::string& name)
//    {
//        for (ChildrenCollection::iterator it = m_children.begin(); it != m_children.end(); ++it)
//        {
//            WidgetPtr child = (*it).second;
//            if (child->GetName() == name)
//                return child;
//
//            boost::shared_ptr<ContainerWidget> container_child = boost::dynamic_pointer_cast<ContainerWidget, Widget>(child);
//            if (container_child.get())
//            {
//                child = container_child->FindChildByName(name);
//                if (child.get())
//                    return child;
//            }
//        }
//        return WidgetPtr();
//    }
//
//    void ContainerWidget::RemoveChildByName(const std::string &name)
//    {
//        WidgetPtr child = FindChildByName(name);
//        if (!child.get())
//            return;
//        Detach(child);
//    }
//}
//PUNK_ENGINE_END
