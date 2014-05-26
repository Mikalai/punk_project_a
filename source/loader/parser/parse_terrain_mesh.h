#ifndef PARSE_TERRAIN_MESH_H
#define PARSE_TERRAIN_MESH_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class TerrainMesh; }
namespace IoModule {
PUNK_ENGINE_LOCAL bool ParseTerrainMesh(Core::Buffer& buffer, Attributes::TerrainMesh& value);
}
PUNK_ENGINE_END

#endif // PARSE_TERRAIN_MESH_H
