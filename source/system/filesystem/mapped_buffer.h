#ifndef _H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER
#define _H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER

#include <config.h>
#include <windows.h>

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
        MappedBuffer(const Core::String& filename, unsigned long wnd_size = 0x4000);
        MappedBuffer(const MappedBuffer&) = delete;
        MappedBuffer& operator = (const MappedBuffer&) = delete;
		~MappedBuffer();
        void* Get(long offset);
        __private::MappedBufferImpl* impl;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_ENGINE_SYSTEM_MAPPED_BUFFER
