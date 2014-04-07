#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <config.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Loader
{
    PUNK_ENGINE_API const Core::String FindPath(const Core::String& filename);
}
PUNK_ENGINE_END

#endif // PATH_FINDER_H
