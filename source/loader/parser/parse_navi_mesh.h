#ifndef PARSE_NAVI_MESH_H
#define PARSE_NAVI_MESH_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace AI { class NaviMesh; }
namespace IoModule {
    extern bool ParseNaviMesh(Core::Buffer& buffer, AI::NaviMesh* value);
}
PUNK_ENGINE_END

#endif // PARSE_NAVI_MESH_H
