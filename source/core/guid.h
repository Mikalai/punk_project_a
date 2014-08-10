#ifndef _H_CORE_GUID
#define _H_CORE_GUID

#include <config.h>
#include <cstdint>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Core {

#define DECLARE_PUNK_GUID(T,V) static const Core::Guid T{ V }
#define DEFINE_PUNK_GUID(T,V) //extern "C" PUNK_ENGINE_API const Core::Guid T{ V }

	class PUNK_ENGINE_API Guid {
	public:
		Guid();
		~Guid();
		Guid(const Guid& value);
		Guid& operator = (const Guid& value);
		Guid(const Core::String& value);
		const Core::String ToString() const;
		void* ToPointer();
		const void* ToPointer() const;
		static const Guid Empty();
	private:
		struct GuidCore {
			std::uint32_t Data1;
			std::uint16_t Data2;
			std::uint16_t Data3;
			std::uint8_t  Data4[8];
		};
		GuidCore m_core;		
        friend PUNK_ENGINE_API bool operator < (const Guid& l, const Guid& r);
        friend PUNK_ENGINE_API bool operator == (const Guid& l, const Guid& r);
	};

	extern PUNK_ENGINE_API bool operator < (const Guid& l, const Guid& r);
	extern PUNK_ENGINE_API bool operator == (const Guid& l, const Guid& r);
	extern PUNK_ENGINE_API bool operator != (const Guid& l, const Guid& r);
}
PUNK_ENGINE_END

#endif	//	_H_CORE_GUID
