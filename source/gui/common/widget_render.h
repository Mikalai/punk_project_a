#ifndef _H_WIDGET_RENDER
#define _H_WIDGET_RENDER

#include "render.h"

namespace Gui
{
	class Widget;
	class ContainerWidget;
    class Image;
	class Button;

	/**
	*	Visitor for rendering gui elements.
	*/
	class WidgetRender
	{
	public:		
		void SetRender(boost::shared_ptr<AbstractRender> value);
		void Render(Widget* widget);
		void Render(ContainerWidget* widget);
		void Render(Button* widget);
        void Render(Image* widget);

	private:
		boost::shared_ptr<AbstractRender> m_render;
	};
}

#endif	//	_H_WIDGET_RENDER
