#ifndef IO_TERRAIN_CELL_H
#define IO_TERRAIN_CELL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
}
namespace Attributes {
    class TerrainCell;
}
namespace IoModule {
    void SaveTerrainCell(Core::Buffer *buffer, const Attributes::TerrainCell* cell);
    void LoadTerrainCell(Core::Buffer *buffer, Attributes::TerrainCell* cell);
}
PUNK_ENGINE_END

#endif // IO_TERRAIN_CELL_H
