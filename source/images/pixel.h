#ifndef _H_PIXEL
#define _H_PIXEL

#include <config.h>
#include "formats.h"
#include "pixel_data_accessor.h"
#include "pixel_size_accessor.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {
	template<ImageFormat format>
	struct Pixel : public PixelDataAccessor < format >, public PixelSizeAccessor < format > {
		Pixel(void* start_address)
		: PixelDataAccessor<format>()
		, PixelSizeAccessor<format>()
		, m_address{ start_address }
	{}

	private:
		void* m_address{ nullptr };
	};
}
PUNK_ENGINE_END

#endif	//	_H_PIXEL