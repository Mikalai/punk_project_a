#ifndef IMAGE_H
#define IMAGE_H

#include "widget.h"

namespace Gui
{
	/**
	*	Image class is used to display a simple picture.
	*	To set a picture to display SetContent should be used.
	*/
    class Image : public Widget
    {
    public:
        Image(float x, float y, float width, float heigh, int order, const std::string& name);
        virtual ~Image();

        void SetContent(boost::shared_ptr<Graphics::ITexture2D> value) { m_image = value; }
        boost::shared_ptr<Graphics::ITexture2D> GetContent() const { return m_image; }

    protected:
        virtual void OnRepaint(WidgetRender* r);

    private:
        boost::shared_ptr<Graphics::ITexture2D> m_image;
    };

    typedef boost::shared_ptr<Image> ImagePtr;
}

#endif // IMAGE_H
