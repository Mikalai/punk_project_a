#ifndef _H_PUNK_IMAGE_MODULE_JPG_IMPORTER
#define _H_PUNK_IMAGE_MODULE_JPG_IMPORTER

#include "importer.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	class Image;

	class JpgImporter : public Importer
	{
	public:
		JpgImporter();

        virtual bool Load(const Core::String& filename);
		virtual bool Load(std::istream& stream, Image* image);
        virtual bool Load(Core::Buffer* buffer, Image* image);

		friend class Importer;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_IMAGE_MODULE_JPG_IMPORTER
