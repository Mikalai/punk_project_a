#ifndef IINDEX_ARRAY_H
#define IINDEX_ARRAY_H

#include <cstdint>
#include <config.h>
#include <core/iobject.h>
PUNK_ENGINE_BEGIN
namespace Graphics {

	DECLARE_PUNK_GUID(IID_IIndexArray, "D233907C-6999-4CC6-8C3E-1FBF89146970");

    class IIndexArray : public Core::IObject {
    public:
        virtual std::uint64_t GetIndexCount() const = 0;
        virtual std::uint64_t GetIndexSize() const = 0;
        virtual std::uint64_t GetMemoryUsage() const = 0;
        virtual void* GetBuffer() = 0;
        virtual const void* GetBuffer() const = 0;
    };
}
PUNK_ENGINE_END


#endif // IINDEX_ARRAY_H
