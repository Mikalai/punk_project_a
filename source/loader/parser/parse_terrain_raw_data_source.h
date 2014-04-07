#ifndef PARSE_TERRAIN_RAW_DATA_SOURCE_H
#define PARSE_TERRAIN_RAW_DATA_SOURCE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer ;}
namespace Attributes { class TerrainRawDataSource; }
namespace Loader {
    extern bool ParseTerrainRawDataSource(Core::Buffer& buffer, Attributes::TerrainRawDataSource& source);
}
PUNK_ENGINE_END

#endif // PARSE_TERRAIN_RAW_DATA_SOURCE_H
