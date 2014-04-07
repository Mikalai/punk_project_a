#ifndef IINDEX_ARRAY_H
#define IINDEX_ARRAY_H

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IIndexArray {
    public:
        virtual std::uint64_t GetIndexCount() const = 0;
        virtual std::uint64_t GetIndexSize() const = 0;
        virtual std::uint64_t GetMemoryUsage() const = 0;
        virtual void* GetIndexBuffer() = 0;
        virtual const void* GetIndexBuffer() const = 0;
    };
}
PUNK_ENGINE_END


#endif // IINDEX_ARRAY_H
