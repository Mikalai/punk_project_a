#include <array>
#include <memory>
#include <tchar.h>
#include "guid.h"

PUNK_ENGINE_BEGIN
namespace Core {
	Guid::Guid() {
		memset(&m_core, 0, sizeof(m_core));
	}

	Guid::Guid(const Core::String& value) {
		const wchar_t* data = (wchar_t*)value.Data();
		const auto ret = swscanf_s(data, L"%8X-%4hX-%4hX-%2hX%2hX-%2hX%2hX%2hX%2hX%2hX%2hX", 
			&m_core.Data1, &m_core.Data2, &m_core.Data3,
			&m_core.Data4[0], &m_core.Data4[1], &m_core.Data4[2], 
			&m_core.Data4[3], &m_core.Data4[4], &m_core.Data4[5], 
			&m_core.Data4[6], &m_core.Data4[7]);
	}

	const Core::String Guid::ToString() const {
		std::array<wchar_t, 40> output;
		_snwprintf_s(output.data(), output.size(), 40, L"%08X-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X", 
			m_core.Data1, m_core.Data2, m_core.Data3, m_core.Data4[0],
			m_core.Data4[1], m_core.Data4[2], m_core.Data4[3], m_core.Data4[4],
			m_core.Data4[5], m_core.Data4[6], m_core.Data4[7]);
		return Core::String(output.data());
	}

	void* Guid::ToPointer() {
		return (void*)this;
	}

	const void* Guid::ToPointer() const {
		return (const void*)this;
	}

	extern PUNK_ENGINE_API bool operator == (const Guid& l, const Guid& r) {
		return !memcmp(l.ToPointer(), r.ToPointer(), sizeof(Guid));
	}

	extern PUNK_ENGINE_API bool operator < (const Guid& l, const Guid& r) {
		return memcmp(l.ToPointer(), r.ToPointer(), sizeof(Guid)) < 0;
	}
}
PUNK_ENGINE_END
