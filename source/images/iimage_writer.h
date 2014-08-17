#ifndef _H_IIMAGE_WRITER
#define _H_IIMAGE_WRITER

#include <config.h>
#include <core/iobject.h>
#include "import_export/image_file_types.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	class IImage;

	DECLARE_PUNK_GUID(IID_IImageWriter, "EC19C2A2-10D6-4FEC-AF54-0565BADF71F0");
	DECLARE_PUNK_GUID(CLSID_ImageWriter, "125DEDCA-4DA9-4685-8B51-A12FA253558F");

	class IImageWriter : public Core::IObject {
	public:
		virtual void Write(IImage* image, Core::Buffer& buffer) = 0;
		virtual void Write(IImage* image, const Core::String& name, ImageFileType encoding) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IIMAGE_WRITER