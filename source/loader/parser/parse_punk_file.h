#ifndef PARSE_PUNK_FILE_H
#define PARSE_PUNK_FILE_H

#include <config.h>
#include <attributes/interface.h>

PUNK_ENGINE_BEGIN
namespace Core
{
    class String;
    class IObject;
}
namespace Loader
{
    extern PUNK_ENGINE_API Core::IObject* ParsePunkFile(const Core::String& path);
}
PUNK_ENGINE_END

#endif // PARSE_PUNK_FILE_H
