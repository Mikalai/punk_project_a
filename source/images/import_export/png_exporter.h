#ifndef _H_PUNK_IMAGE_PNG_EXPORTER
#define _H_PUNK_IMAGE_PNG_EXPORTER

#include "exporter.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	class PngExporter : public Exporter
	{
	public:
        virtual void Export(const Core::String& filename, const Image& image);
	};
}
PUNK_ENGINE_END

#endif
