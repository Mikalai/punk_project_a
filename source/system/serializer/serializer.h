#ifndef _H_SYSTEM_SERIALIZER
#define _H_SYSTEM_SERIALIZER

#include <config.h>
#include <cstdint>
#include <core/iserializable.h>

PUNK_ENGINE_BEGIN
namespace System {

	template<typename T> struct Pack;
	template<typename T> struct Unpack;

	template<>
	struct Pack < bool > {
		static void Do(bool& value, std::uint8_t(&buf)[1]) {
			buf[0] = value ? 1 : 0;
		}
	};
	
	template<>
	struct Pack < std::int64_t > {
		static void Do(std::int64_t& value, std::uint8_t(&buf)[8]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
			buf[2] = (value >> 16) & 0xFF;
			buf[3] = (value >> 24) & 0xFF;
			buf[4] = (value >> 32) & 0xFF;
			buf[5] = (value >> 40) & 0xFF;
			buf[6] = (value >> 48) & 0xFF;
			buf[7] = (value >> 56) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::int64_t > {
		static void Do(std::int64_t& value, std::uint8_t(&buf)[8]) {
			value = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24 |
				buf[4] << 32 | buf[5] << 40 | value << 48 | buf[7] << 56;
		}
	};

	template<>
	struct Pack < std::uint64_t > {
		static void Do(std::uint64_t& value, std::uint8_t(&buf)[8]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
			buf[2] = (value >> 16) & 0xFF;
			buf[3] = (value >> 24) & 0xFF;
			buf[4] = (value >> 32) & 0xFF;
			buf[5] = (value >> 40) & 0xFF;
			buf[6] = (value >> 48) & 0xFF;
			buf[7] = (value >> 56) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::uint64_t > {
		static void Do(std::uint64_t& value, std::uint8_t(&buf)[8]) {
			value = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24 |
				buf[4] << 32 | buf[5] << 40 | value << 48 | buf[7] << 56;
		}
	};

	template<>
	struct Pack < std::int32_t > {
		static void Do(std::int32_t& value, std::uint8_t(&buf)[4]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
			buf[2] = (value >> 16) & 0xFF;
			buf[3] = (value >> 24) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::int32_t > {
		static void Do(std::int32_t& value, std::uint8_t(&buf)[4]) {
			value = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
		}
	};

	template<>
	struct Pack < std::uint32_t > {
		static void Do(std::uint32_t& value, std::uint8_t(&buf)[4]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
			buf[2] = (value >> 16) & 0xFF;
			buf[3] = (value >> 24) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::uint32_t > {
		static void Do(std::uint32_t& value, std::uint8_t(&buf)[4]) {
			value = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
		}
	};

	template<>
	struct Pack < std::int16_t > {
		static void Do(std::int16_t& value, std::uint8_t(&buf)[2]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::int16_t > {
		static void Do(std::int16_t& value, std::uint8_t(&buf)[2]) {
			value = buf[0] | buf[1] << 8;
		}
	};

	template<>
	struct Pack < std::uint16_t > {
		static void Do(std::uint16_t& value, std::uint8_t(&buf)[2]) {
			buf[0] = value & 0xFF;
			buf[1] = (value >> 8) & 0xFF;
		}
	};

	template<>
	struct Unpack < std::uint16_t > {
		static void Do(std::uint16_t& value, std::uint8_t(&buf)[2]) {
			value = buf[0] | buf[1] << 8;
		}
	};

	template<>
	struct Unpack < float > {
		static void Do(float& value, std::uint8_t(&buf)[4]) {
			std::uint32_t v;
			Unpack<std::uint32_t>::Do(v, buf);
			value = *(float*)&v;
		}
	};

	template<>
	struct Pack < float > {
		static void Do(float& value, std::uint8_t(&buf)[4]) {
			std::uint32_t v = *(std::uint32_t*)&value;
			Pack<std::uint32_t>::Do(v, buf);
		}
	};

	template<>
	struct Unpack < double > {
		static void Do(double& value, std::uint8_t(&buf)[8]) {
			std::uint64_t v;
			Unpack<std::uint64_t>::Do(v, buf);
			value = *(float*)&v;
		}
	};

	template<>
	struct Pack < double > {
		static void Do(float& value, std::uint8_t(&buf)[8]) {
			std::uint64_t v = *(std::uint64_t*)&value;
			Pack<std::uint64_t>::Do(v, buf);
		}
	};

	template<typename T>
	class Serializer : public Core::ISerializable, public SerializePod<T> {
	public:
		Serializer(T& value) 
			: m_value{ value } {}

		void Serialize(Core::Buffer& buffer) {
			std::uint8_t buf[sizeof(T)];
			Pack(m_value)
		}
	private:
		T& m_value;
	};
}
PUNK_ENGINE_END

#endif	//	_H_SYSTEM_SERIALIZER