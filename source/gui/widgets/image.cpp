#include "image.h"
#include "../common/picture.h"
#include "../common/widget_render.h"

namespace Gui
{
    Image::Image(float x, float y, float width, float height, int order, const std::string& name)
        : Widget(x, y, width, height, order, name)
    {
        m_image.reset();
    }

    void Image::OnRepaint(WidgetRender *r)
    {
        if (IsVisible())
            r->Render(this);
    }

    Image::~Image()
    {}
}
