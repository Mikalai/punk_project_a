#ifndef _H_PUNK_IMAGE_MODULE_PNG_IMPORTER
#define _H_PUNK_IMAGE_MODULE_PNG_IMPORTER

#include "importer.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	class Image;

	class PngImporter : public Importer
	{
	public:
		PngImporter();

        virtual bool Load(const Core::String& filename);
		virtual bool Load(std::istream& stream, Image* image);
        virtual void Load(Core::Buffer* buffer, Image* image);

		friend class Importer;
	};
}
PUNK_ENGINE_END

#endif
