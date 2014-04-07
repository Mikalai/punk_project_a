#include <ai/module.h>
#include <math/weighted_point.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_weighted_point.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseWeightedPoint(Core::Buffer &buffer, Math::WeightedPoint& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
            {
                return true;
            }
            case WORD_WEIGHT:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.SetWeight(v);
            }
            break;
            case WORD_POSITION:
            {
                Math::vec4 v;
                ParseBlockedVector4f(buffer, v);
                value.SetPoint(v);
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
