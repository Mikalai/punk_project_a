#ifndef _H_PUNK_IMAGE_EXPORTER
#define _H_PUNK_IMAGE_EXPORTER

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace ImageModule
{
	class IImage;

	class PUNK_ENGINE_API Exporter
	{
	public:
        virtual void Export(const Core::String& filename, const IImage* image);
	};
}
PUNK_ENGINE_END

#endif
