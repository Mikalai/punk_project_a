#include <attributes/terrain/terrain_mesh.h>
#include "parse_simple.h"
#include "parser.h"
#include "parse_terrain_mesh.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    bool ParseTerrainMesh(Core::Buffer& buffer, Attributes::TerrainMesh& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            const Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_MESH:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                value.SetStaticMeshFilename(name);
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
