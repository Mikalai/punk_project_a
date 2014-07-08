//#ifndef _H_ABSTRACT_PICTURE
//#define _H_ABSTRACT_PICTURE
//
//#include <config.h>
//
//PUNK_ENGINE_BEGIN
//namespace Gui
//{
//	/**
//	*	Abstract picture class that is used by Style and Image classes
//	*	to draw pictures on the gui elements.
//	*
//	*/
//    class Graphics::ITexture2D
//	{
//	public:
//        virtual ~Graphics::ITexture2D() {}
//	};
//
//    typedef Graphics::ITexture2D* Graphics::ITexture2DPtr;
//
//	/**
//	*	Abstract class that is used by manager, when creating gui from xml file.
//	*/
//    class Graphics::ITexture2DFactory
//    {
//    public:
//        virtual Graphics::ITexture2D* Create(const std::string& filename, float x, float y, float width, float height) = 0;
//        virtual ~Graphics::ITexture2DFactory() {}
//    };
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_ABSTRACT_IMAGE
