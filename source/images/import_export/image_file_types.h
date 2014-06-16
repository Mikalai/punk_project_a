#ifndef _H_IMAGE_FILE_TYPES
#define _H_IMAGE_FILE_TYPES

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace ImageModule {
	enum class ImageFileType : std::uint32_t {
		Bad,
		Jpeg,
		Tga,
		Tiff,
		Bmp,
		Png,
		Gif
	};
}
PUNK_ENGINE_END

#endif	//	_H_IMAGE_FILE_TYPES