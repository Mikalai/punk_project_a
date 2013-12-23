#ifndef _H_ABSTRACT_PICTURE
#define _H_ABSTRACT_PICTURE

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Gui
{
	/**
	*	Abstract picture class that is used by Style and Image classes
	*	to draw pictures on the gui elements.
	*
	*/
    class AbstractPicture
	{
	public:
        virtual ~AbstractPicture() {}
	};

    typedef AbstractPicture* AbstractPicturePtr;

	/**
	*	Abstract class that is used by manager, when creating gui from xml file.
	*/
    class AbstractPictureFactory
    {
    public:
        virtual AbstractPicture* Create(const std::string& filename, float x, float y, float width, float height) = 0;
        virtual ~AbstractPictureFactory() {}
    };
}
PUNK_ENGINE_END

#endif	//	_H_ABSTRACT_IMAGE
