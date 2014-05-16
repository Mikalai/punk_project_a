#ifndef _H_PUNK_VIDEO_DRIVER_INTERFACE
#define _H_PUNK_VIDEO_DRIVER_INTERFACE

#include <memory>
#include <config.h>
#include <images/formats.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Image { class Image; }
namespace Core {
	class String;
	class Buffer;
}
namespace Graphics {

	class IRenderTarget;
	class ITexture2D;
	class ITexture2DArray;
	class Frame;
	class FrameBufferConfig;
	class IFrameBuffer;
	class ICanvas;
	class IVideoDriverSettings;
	class IRender;

	class PUNK_ENGINE_API IVideoDriver
	{
	public:
		virtual ICanvas* GetCanvas() = 0;		
		virtual IVideoDriverSettings* GetSettings() = 0;
		virtual IRender* GetRender() = 0;
	};

	using IVideoDriverUniquePtr = std::unique_ptr < IVideoDriver, void(*)(IVideoDriver*) > ;

	extern PUNK_ENGINE_API IVideoDriverUniquePtr CreateVideoDriver(ICanvas* canvas);
	extern PUNK_ENGINE_API void DestroyVideoDriver(IVideoDriver* driver);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER_INTERFACE
