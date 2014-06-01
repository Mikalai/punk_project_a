#include "exporter.h"
#include "png_exporter.h"
#include "images/error/module.h"
#include "images/internal_images/image.h"
#include "string/string.h"

PUNK_ENGINE_BEGIN
namespace ImageModule
{
    void Exporter::Export(const Core::String& filename, const IImage* image)
    {
        if (filename.EndWith(".png"))
		{
			PngExporter importer;
			importer.Export(filename, image);			
		}
		else
            throw Error::ImageException(L"Unsupported file format");
	}
}
PUNK_ENGINE_END
