#ifndef _H_PUNK_OPENGL_INDEX_BUFFER_INTERFACE
#define _H_PUNK_OPENGL_INDEX_BUFFER_INTERFACE

#include <cstdint>
#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVideoMemory;

	DECLARE_PUNK_GUID(IID_IBufferObject, "471E1C90-5A9C-4790-9C09-5E575D195EBB");

    class IBufferObject : public virtual Core::IObject {
    public:
        virtual void Create(const void* data, std::uint32_t m_size) = 0;
        virtual void Destroy() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void* Map() = 0;
        virtual const void* Map() const = 0;
        virtual void Unmap() const = 0;
        virtual void CopyData(const void* data, std::uint32_t size) = 0;
        virtual bool IsValid() const = 0;
        virtual std::uint32_t GetSize() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_INDEX_BUFFER
