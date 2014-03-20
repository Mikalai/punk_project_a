#ifndef _H_PUNK_VIDEO_DRIVER_INTERFACE
#define _H_PUNK_VIDEO_DRIVER_INTERFACE

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

    class PUNK_ENGINE_API IVideoDriver
	{
	public:
        virtual ICanvas* GetCanvas() = 0;        
        virtual Frame* BeginFrame() = 0;
        virtual void EndFrame(Frame* value) = 0;
        virtual IVideoDriverSettings* GetSettings() = 0;
	};

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IVideoDriver* CreateVideoDriver(ICanvas* canvas);
        extern "C" PUNK_ENGINE_API void DestroyVideoDriver(IVideoDriver* driver);
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER_INTERFACE
