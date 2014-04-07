#include <attributes/data/lights/directional_light.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_directional_light.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseDirectionalLight(Core::Buffer& buffer, Attributes::DirectionalLight* value)
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
            case WORD_ENERGY:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value->SetEnergy(v);
            }
                break;
            case WORD_COLOR:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value->SetColor(v);
            }
                break;
            case WORD_DIRECTION:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value->SetDirection(v);
            }
                break;
            case WORD_DISTANCE:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value->SetDistance(v);
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
