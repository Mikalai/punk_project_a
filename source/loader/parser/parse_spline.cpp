#include <ai/module.h>
#include <math/spline.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_weighted_point.h"
#include "parse_spline.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseSpline(Core::Buffer &buffer, Math::Spline &value)
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
            case WORD_POINT:
            {
                Math::WeightedPoint p;
                ParseWeightedPoint(buffer, p);
                value.AddPoint(p);
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
