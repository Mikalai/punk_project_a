#ifndef IO_CURVE_PATH_H
#define IO_CURVE_PATH_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Object;
    class Buffer;
}
namespace Loader {
    void SaveCurvePath(Core::Buffer *buffer, const Core::Object *o);
    void LoadCurvePath(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_CURVE_PATH_H
