#ifndef IVERTEX_ARRAY_H
#define IVERTEX_ARRAY_H

#include <cstdint>
#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

	DECLARE_PUNK_GUID(IID_IVertexArray, "483898B7-9DE0-4CA8-909C-8D48C78CF2BE");
    class IVertexArray : public Core::IObject {
    public:
        //virtual ~IVertexArray() = 0;
        virtual std::uint64_t GetVertexType() const = 0;
        virtual std::uint64_t GetVertexCount() const = 0;
        virtual std::uint64_t GetVertexSize() const = 0;
        virtual std::uint64_t GetMemoryUsage() const = 0;
        virtual void* GetBuffer() = 0;
        virtual const void* GetBuffer() const = 0;
    };
}
PUNK_ENGINE_END

#endif // IVERTEX_ARRAY_H
