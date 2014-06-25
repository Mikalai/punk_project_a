#include <system/factory/module.h>
#include <ai/icurvepath.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseCurvePath(Core::Buffer &buffer, void* object)
    {
		AI::ICurvePath *value = (AI::ICurvePath*)object;
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
            case WORD_SPLINE:
            {
				Math::ISpline* spline{ nullptr };
                parser->Parse(WORD_SPLINE, buffer, spline);
                value->AddSpline(spline);
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_CURVE_PATH, ParseCurvePath);

}
PUNK_ENGINE_END
