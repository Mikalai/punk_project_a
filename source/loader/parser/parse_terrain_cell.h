#ifndef PARSE_TERRAIN_CELL_H
#define PARSE_TERRAIN_CELL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class TerrainCell; }
namespace IoModule {
    extern bool ParseTerrainCell(Core::Buffer& buffer, Attributes::TerrainCell& cell);
}
PUNK_ENGINE_END

#endif // PARSE_TERRAIN_CELL_H
