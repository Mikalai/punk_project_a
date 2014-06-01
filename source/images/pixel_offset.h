#ifndef _H_PIXEL_OFFSET
#define _H_PIXEL_OFFSET

#include <config.h>
#include "formats.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	template<ImageFormat format> struct PixelOffsetAccessor;

	template<>
	struct PixelOffsetAccessor < ImageFormat::RGBA > {
		static std::uint32_t Offset
	};
}
PUNK_ENGINE_END

#endif	//	_H_PIXEL_OFFSET