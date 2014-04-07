#ifndef PARSE_PUNK_FILE_H
#define PARSE_PUNK_FILE_H

#include <config.h>
#include <attributes/interface.h>

PUNK_ENGINE_BEGIN
namespace Core
{
    class String;
    class Object;
}
namespace Loader
{
    extern PUNK_ENGINE_API Core::Object* ParsePunkFile(const Core::String& path);
}
PUNK_ENGINE_END

#endif // PARSE_PUNK_FILE_H
