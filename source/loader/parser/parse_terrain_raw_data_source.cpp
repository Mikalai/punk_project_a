#include <attributes/terrain/module.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_terrain_raw_data_source.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseTerrainRawDataSource(Core::Buffer& buffer, Attributes::TerrainRawDataSource& source)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_REF:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
                source.SetRawFile(value);
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
