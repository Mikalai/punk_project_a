#ifndef PARSE_SKIN_MESH_H
#define PARSE_SKIN_MESH_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class SkinGeometry; }
namespace Loader {
    extern bool ParseSkinMesh(Core::Buffer& buffer, Attributes::SkinGeometry* geometry);
}
PUNK_ENGINE_END

#endif // PARSE_SKIN_MESH_H
