#ifndef _H_IIMAGE_READER
#define _H_IIMAGE_READER

#include <config.h>
#include <string/module.h>
#include <core/iobject.h>
#include <core/action.h>

PUNK_ENGINE_BEGIN
namespace ImageModule {

	class IImage;

	DECLARE_PUNK_GUID(IID_IImageReader, "93C2826B-6F2D-4672-A8F0-C04608E64A40");

	class IImageReader : public Core::IObject {
	public:
		//virtual void SetSource(const Core::String& filename) = 0;
		//virtual void SetSource(const Core::Buffer* buffer) = 0;
		//virtual void Run() = 0;
		//virtual void Run(Core::ActionBase<IImage*>* callback) = 0;
		//virtual IImage* GetResult() = 0;

		virtual IImage* Read(const Core::String& filename) = 0;
		virtual IImage* Read(Core::Buffer& buffer) = 0;
	};

	using IImageReaderPointer = Core::Pointer < IImageReader > ;
}
PUNK_ENGINE_END

#endif	//	_H_IIMAGE_READER