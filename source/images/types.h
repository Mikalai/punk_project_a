#ifndef _H_IMAGE_DATA_TYPES
#define _H_IMAGE_DATA_TYPES

#include <config.h>
#include <cstdint>
#include <images/error/module.h>

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

	inline std::uint32_t GetSize(DataType value) {
		switch (value)
		{
		case DataType::Byte:
			return 1;
		case DataType::UnsignedShort:
			return 2;
		case DataType::SignedShort:
			return 2;
		case DataType::SignedInt:
			return 4;
		case DataType::UnsignedInt:
			return 4;
		case DataType::Float:
			return 4;
		}
		throw Error::ImageException("Unknown data type");
	}

	template<DataType type> struct GetDataTypeSize;

	template<> struct GetDataTypeSize < DataType::Byte > {
		static constexpr std::uint32_t Value() {
			return 1;
		}
	};

	template<> struct GetDataTypeSize < DataType::UnsignedShort > {
		static constexpr std::uint32_t Value() {
			return 2;
		}
	};

	template<> struct GetDataTypeSize < DataType::SignedShort > {
		static constexpr std::uint32_t Value() {
			return 2;
		}
	};

	template<> struct GetDataTypeSize < DataType::UnsignedInt > {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};

	template<> struct GetDataTypeSize < DataType::SignedInt > {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};

	template<> struct GetDataTypeSize < DataType::Float > {
		static constexpr std::uint32_t Value() {
			return 4;
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_IMAGE_DATA_TYPES