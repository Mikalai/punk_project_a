#include <string/module.h>
#include <array>
#include <memory.h>
#include "guid.h"

#ifdef WIN32
#include <tchar.h>
#include <initguid.h>
#include <objbase.h>
#endif

PUNK_ENGINE_BEGIN
namespace Core {

    Guid::Guid() {
		memset(&m_core, 0, sizeof(m_core));
	}

	Guid::~Guid() {
		memset(&m_core, 0, sizeof(m_core));
	}

	Guid::Guid(const Guid& value) {
		if (this != &value) {
			m_core = value.m_core;
		}
	}

	Guid& Guid::operator = (const Guid& value) {
		if (this != &value) {
			m_core = value.m_core;
		}
		return *this;
	}

	Guid::Guid(const Core::String& value) {		
		Core::Buffer buffer = value.ToWchar();
		const wchar_t* buf = (const wchar_t*)buffer.Data();
		std::uint16_t data[8];
#ifdef WIN32
		const auto ret = swscanf_s(buf, L"%8X-%4hX-%4hX-%2hX%2hX-%2hX%2hX%2hX%2hX%2hX%2hX\0", 
			&m_core.Data1, &m_core.Data2, &m_core.Data3,
			&data[0], &data[1], &data[2],
			&data[3], &data[4], &data[5],
			&data[6], &data[7]);		
#elif defined __linux__
        const auto ret = swscanf(buf, L"%8X-%4hX-%4hX-%2hX%2hX-%2hX%2hX%2hX%2hX%2hX%2hX\0",
            &m_core.Data1, &m_core.Data2, &m_core.Data3,
            &data[0], &data[1], &data[2],
            &data[3], &data[4], &data[5],
            &data[6], &data[7]);
#endif
		for (int i = 0; i < 8; ++i){
			m_core.Data4[i] = (std::uint8_t)data[i];
		}
	}

	const Core::String Guid::ToString() const {
		std::array<wchar_t, 40> output;
#ifdef WIN32
		_snwprintf_s(output.data(), output.size(), 40, L"%08X-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X", 
			m_core.Data1, m_core.Data2, m_core.Data3, m_core.Data4[0],
			(std::uint16_t)m_core.Data4[1], (std::uint16_t)m_core.Data4[2], (std::uint16_t)m_core.Data4[3], (std::uint16_t)m_core.Data4[4],
			(std::uint16_t)m_core.Data4[5], (std::uint16_t)m_core.Data4[6], (std::uint16_t)m_core.Data4[7]);
#elif defined __linux__
        swprintf(output.data(), 40, L"%08X-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X",
            m_core.Data1, m_core.Data2, m_core.Data3, m_core.Data4[0],
            (std::uint16_t)m_core.Data4[1], (std::uint16_t)m_core.Data4[2], (std::uint16_t)m_core.Data4[3], (std::uint16_t)m_core.Data4[4],
            (std::uint16_t)m_core.Data4[5], (std::uint16_t)m_core.Data4[6], (std::uint16_t)m_core.Data4[7]);
#endif
		return Core::String(output.data());
	}

	void* Guid::ToPointer() {
		return (void*)this;
	}


	const Guid Guid::Empty() {
		return Guid{};
	}

	const void* Guid::ToPointer() const {
		return (const void*)this;
	}

	extern PUNK_ENGINE_API bool operator == (const Guid& l, const Guid& r) {
		return !memcmp(l.ToPointer(), r.ToPointer(), sizeof(Guid));
	}

	extern PUNK_ENGINE_API bool operator != (const Guid& l, const Guid& r) {
		return !(l == r);
	}

	extern PUNK_ENGINE_API bool operator < (const Guid& l, const Guid& r) {
		return memcmp(l.ToPointer(), r.ToPointer(), sizeof(Guid)) < 0;
	}
}
PUNK_ENGINE_END
