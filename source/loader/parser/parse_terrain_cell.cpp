#include <attributes/terrain/module.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_terrain_raw_data_source.h"
#include "parse_terrain_cell.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseTerrainCell(Core::Buffer& buffer, Attributes::TerrainCell& cell)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
                cell.SetName(value);
            }
                break;
            case WORD_LOCATION:
            {
                Math::ivec2 value;
                ParseBlockedVector2i(buffer, value);
                cell.SetLocation(value);
            }
                break;
            case WORD_RAW_DATA_SOURCE:
            {
                Attributes::TerrainRawDataSource value;
                ParseTerrainRawDataSource(buffer, value);
                cell.SetRawDataSource(value);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
PUNK_ENGINE_END
