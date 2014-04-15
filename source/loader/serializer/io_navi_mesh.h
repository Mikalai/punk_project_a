#ifndef IO_NAVI_MESH_H
#define IO_NAVI_MESH_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveNaviMesh(Core::Buffer *buffer, const Core::Object *o);
    void LoadNaviMesh(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_NAVI_MESH_H
