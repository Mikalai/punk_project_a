#ifndef _H_PIXEL_SIZE_ACCESSOR
#define _H_PIXEL_SIZE_ACCESSOR

#include <config.h>
#include "formats.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	template<ImageFormat format> struct PixelSizeAccessor;

	template<>
	struct PixelSizeAccessor < ImageFormat::RGBA > {
		constexpr static std::uint32_t GetSize() {
			return 4 * GetDataTypeSize<DataType::Byte>::Value();
		}
	};

	template<>
	struct PixelSizeAccessor < ImageFormat::RGB > {
		constexpr static std::uint32_t GetSize() {
			return 3 * GetDataTypeSize<DataType::Byte>::Value();
		}
	};

	template<>
	struct PixelSizeAccessor < ImageFormat::ALPHA > {
		constexpr static std::uint32_t GetSize() {
			return GetDataTypeSize<DataType::Byte>::Value();
		}
	};

}
PUNK_ENGINE_END


#endif	//	_H_PIXEL_SIZE_ACCESSOR