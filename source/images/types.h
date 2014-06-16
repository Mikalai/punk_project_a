#ifndef _H_IMAGE_DATA_TYPES
#define _H_IMAGE_DATA_TYPES

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace ImageModule {

	enum class DataType : std::uint32_t {
		Byte,
		UnsignedShort,
		SignedShort,
		SignedInt,
		UnsignedInt,
		Float
	};

	template<DataType type> struct GetDataTypeSize; 

	template<> struct GetDataTypeSize<DataType::Byte> {
		static constexpr std::uint32_t Value() {
			return 1;
		}
	};

	template<> struct GetDataTypeSize<DataType::UnsignedShort> {
		static constexpr std::uint32_t Value() {
			return 2;
		}
	};

	template<> struct GetDataTypeSize<DataType::SignedShort> {
		static constexpr std::uint32_t Value() {
			return 2;
		}
	};

	template<> struct GetDataTypeSize<DataType::UnsignedInt> {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};

	template<> struct GetDataTypeSize<DataType::SignedInt> {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};

	template<> struct GetDataTypeSize<DataType::Float> {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_IMAGE_DATA_TYPES