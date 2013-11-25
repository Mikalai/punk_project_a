#ifndef _H_PUNK_IMAGE_RGBA_IMAGE
#define _H_PUNK_IMAGE_RGBA_IMAGE

#include "config.h"
#include "image.h"
#include <memory>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Image
{
	class PUNK_ENGINE_API RGBAImage : public Image
	{
	public:
		RGBAImage();
		RGBAImage(const RGBAImage& image);
		RGBAImage& operator = (const RGBAImage& image);
	};

    std::unique_ptr<RGBAImage> ImportRGBAImage(const Core::String& filename);
    void ExportRGBAImage(const RGBAImage& image, const Core::String& filename);
}
PUNK_ENGINE_END

#endif
