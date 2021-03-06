#ifndef _H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER
#define _H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
}
namespace System {
    namespace __private {
        struct MappedBufferImpl;
    }

    class PUNK_ENGINE_API MappedBuffer
	{
	public:
        MappedBuffer(const Core::String& filename, std::uint32_t wnd_size = 0x4000);
        MappedBuffer(const MappedBuffer&) = delete;
        MappedBuffer& operator = (const MappedBuffer&) = delete;
		~MappedBuffer();
        void* Get(std::uint32_t offset);
        __private::MappedBufferImpl* impl;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER
