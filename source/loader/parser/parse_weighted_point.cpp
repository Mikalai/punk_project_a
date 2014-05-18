#include <math/weighted_point.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseWeightedPoint(Core::Buffer &buffer,  void* object)
    {
		Parser* parser = GetDefaultParser();
		Math::WeightedPoint* value = (Math::WeightedPoint*)object;
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
            case WORD_WEIGHT:
            {
                float v;
                parser->Parse(WORD_FLOAT, buffer, v);
                value->SetWeight(v);
            }
            break;
            case WORD_POSITION:
            {
                Math::vec4 v;
                parser->Parse(WORD_VEC3F, buffer, v);
                value->SetPoint(v);
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_WEIGHTED_POINT, ParseWeightedPoint);
}
PUNK_ENGINE_END
