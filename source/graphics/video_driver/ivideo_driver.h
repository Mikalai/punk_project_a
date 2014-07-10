#ifndef _H_PUNK_VIDEO_DRIVER_INTERFACE
#define _H_PUNK_VIDEO_DRIVER_INTERFACE

#include <memory>
#include <config.h>
#include <core/iobject.h>
#include <images/formats.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace ImageModule { class Image; }
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
	class ILowLevelRender;

	DECLARE_PUNK_GUID(IID_IVideoDriver, "A40FB690-DB16-44BA-AAE7-8F6D00315085");
	DECLARE_PUNK_GUID(CLSID_VideoDriver, "734BD528-965F-4D6D-9CAA-EFAE29B1F947");

	class PUNK_ENGINE_API IVideoDriver : public Core::IObject
	{
	public:
		virtual void Initialize(ICanvas* canvas) = 0;
		virtual ICanvas* GetCanvas() = 0;		
		virtual IVideoDriverSettings* GetSettings() = 0;
		virtual ILowLevelRender* GetRender() = 0;
	};

	using IVideoDriverPointer = Core::Pointer < IVideoDriver > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER_INTERFACE
