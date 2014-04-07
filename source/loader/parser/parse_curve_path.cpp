#include <ai/module.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_spline.h"
#include "parse_curve_path.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseCurvePath(Core::Buffer &buffer, AI::CurvePath *value)
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
            case WORD_SPLINE:
            {
                Math::Spline spline;
                ParseSpline(buffer, spline);
                value->AddSpline(spline);
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
