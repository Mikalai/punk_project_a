#include <ai/module.h>
#include <math/spline.h>
#include "parser.h"
#include "parse_weighted_point.h"
#include "parse_spline.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseSpline(Core::Buffer &buffer, void* object)
    {
		Math::ISpline* value = (Math::ISpline*)object;
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
            {
                return true;
            }
            case WORD_WEIGHTED_POINT:
            {
                Math::WeightedPoint p;
                parser->Parse(WORD_WEIGHTED_POINT, buffer, p);
                value->AddPoint(p);
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_SPLINE, ParseSpline);
}
PUNK_ENGINE_END
