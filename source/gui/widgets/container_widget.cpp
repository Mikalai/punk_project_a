#include <stdexcept>
#include <string>
#include "container_widget.h"
#include "../common/style.h"
#include "../common/widget_render.h"
#include "widget.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
    ContainerWidget::ContainerWidget(float x, float y, float width, float height, int order, const std::string& name)
        : Widget(x, y, width, height, order, name)
    {
        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR, 0.3, 0.3, 0.3, 0.4);
        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_MOUSE_OVER, 0.3, 0.3, 0.3, 0.5);
        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_FOCUSED, 0.3, 0.3, 0.3, 0.9);
        //GetStyle()->SetBackColor(Gui::Style::BACK_COLOR_MOUSE_PRESSED, 0.3, 0.3, 0.3, 1.0);
    }

    ContainerWidget::~ContainerWidget()
    {}

	WidgetPtr ContainerWidget::GetWidget(float x, float y)
	{
		WidgetPtr res;

		for (ChildrenCollection::iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			WidgetPtr child = (*it).second;
            if (child->IsVisible())
			{
                if (x < child->GetLocalX() || x > child->GetLocalX() + child->GetWidth())
					continue;
                if (y < child->GetLocalY() || y > child->GetLocalY() + child->GetHeight())
					continue;		

				boost::shared_ptr<ContainerWidget> child_container(boost::dynamic_pointer_cast<ContainerWidget, Widget>(child));
				if (child_container.get())
				{
                    res = child_container->GetWidget(x - child->GetLocalX(), y - child->GetLocalY());
					if (res.get())
						return res;
				}

				res = child;
			}
		}
		return res;
	}

    void ContainerWidget::AddWidget(WidgetPtr value)
	{
        ChildrenCollection::iterator low = m_children.lower_bound(value->GetOrder());
        ChildrenCollection::iterator up = m_children.upper_bound(value->GetOrder());
		ChildrenCollection::iterator it = low;
		
		for (; it != low; ++it)
		{
			if ((*it).second.get() == value.get())
				return;
		}
		
        m_children.insert(std::make_pair<int, WidgetPtr >(value->GetOrder(), value));
	}

	void ContainerWidget::RemoveWidget(WidgetPtr value)
	{
        ChildrenCollection::iterator low = m_children.lower_bound(value->GetOrder());
        ChildrenCollection::iterator up = m_children.upper_bound(value->GetOrder());

		if (low == m_children.end())
			return;

		ChildrenCollection::iterator it;
		for (it = low; it != up; ++it)
		{
			if ((*it).second.get() == value.get())
				break;
		}

		if (it == m_children.end())
			return;
		m_children.erase(it);
	}

	void Attach(WidgetPtr child, boost::shared_ptr<ContainerWidget> parent)
	{
		if (child->Parent().lock().get())
			Detach(child);
		parent->AddWidget(child);
		child->Parent(parent);
	}

	void Detach(WidgetPtr widget)
	{
		boost::shared_ptr<ContainerWidget> parent = widget->Parent().lock();
		if (!parent.get())
			return;
		parent->RemoveWidget(widget);
	}

    void ContainerWidget::OnRepaint(WidgetRender *r)
    {
        if (!IsVisible())
            return;
        r->Render(this);
    }

    WidgetPtr ContainerWidget::FindChildByName(const std::string& name)
    {
        for (ChildrenCollection::iterator it = m_children.begin(); it != m_children.end(); ++it)
        {
            WidgetPtr child = (*it).second;
            if (child->GetName() == name)
                return child;

            boost::shared_ptr<ContainerWidget> container_child = boost::dynamic_pointer_cast<ContainerWidget, Widget>(child);
            if (container_child.get())
            {
                child = container_child->FindChildByName(name);
                if (child.get())
                    return child;
            }
        }
        return WidgetPtr();
    }

    void ContainerWidget::RemoveChildByName(const std::string &name)
    {
        WidgetPtr child = FindChildByName(name);
        if (!child.get())
            return;
        Detach(child);
    }
}
PUNK_ENGINE_END
