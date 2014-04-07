#include <attributes/water/module.h>
#include "parser.h"
#include "parse_simple.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseRiver(Core::Buffer &buffer, Attributes::River &value)
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
            case WORD_FLOW_SPEED:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.SetFlowSpeed(v);
            }
            break;
            case WORD_FLOW_DIRECTION:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value.SetFlowDirection(v);
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
