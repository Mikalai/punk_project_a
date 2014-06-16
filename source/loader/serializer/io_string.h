#ifndef IO_STRING_H
#define IO_STRING_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class String;
}
namespace IoModule {
    void SaveString(Core::Buffer* buffer, const Core::String& value);
    void LoadString(Core::Buffer* buffer, Core::String& value);
}
PUNK_ENGINE_END

#endif // IO_STRING_H
