#ifndef _H_SERIALIZER
#define _H_SERIALIZER

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class IObject;
}
namespace IoModule {
    PUNK_ENGINE_API void RegisterSerializer(std::int64_t type, void (*save)(Core::Buffer*, const Core::IObject*), void (*load)(Core::Buffer*, Core::IObject*));
    PUNK_ENGINE_API void (*GetSaver(std::int64_t type))(Core::Buffer*, const Core::IObject*);
    PUNK_ENGINE_API void (*GetLoader(std::int64_t type))(Core::Buffer*, Core::IObject*);
}
PUNK_ENGINE_END

#endif  //  _H_SERIALIZER
