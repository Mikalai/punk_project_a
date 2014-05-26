#include <attributes/terrain/module.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_terrain_cell.h"
#include "parse_map_description.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseMapDescription(Core::Buffer& buffer, Attributes::Terrain* terrain)
    {
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(ParseKeyword(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NUM_BLOCKS:
            {
                int value;
                ParseBlockedInteger(buffer, value);
                terrain->SetNumBlocks(value);
            }
                break;
            case WORD_BLOCK_SCALE:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                terrain->SetBlockScale(value);
            }
                break;
            case WORD_BLOCK_SIZE:
            {
                int value;
                ParseBlockedInteger(buffer, value);
                terrain->SetBlocksSize(value);
            }
                break;
            case WORD_HEIGHT_SCALE:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                terrain->SetHeightScale(value);
            }
                break;
            case WORD_WORLD_ORIGIN:
            {
                Math::vec2 value;
                ParseBlockedVector2f(buffer, value);
                terrain->SetOrigin(value);
            }
                break;
            case WORD_CELL:
            {
                Attributes::TerrainCell value;
                ParseTerrainCell(buffer, value);
                value.Validate();
                terrain->AddOrUpdateCell(value);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return true;
    }
}
PUNK_ENGINE_END
