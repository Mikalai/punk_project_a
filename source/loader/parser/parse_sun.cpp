//#include <attributes/data/lights/sun.h>
//#include "parser.h"
//#include "parse_simple.h"
//#include "parse_sun.h"
//
//PUNK_ENGINE_BEGIN
//namespace Loader
//{
//    bool ParseSun(Core::Buffer &buffer, Attributes::Sun &value)
//    {
//        CHECK_START(buffer);
//        while (1)
//        {
//            const Core::String word = buffer.ReadWord();
//            KeywordCode code = ParseKeyword(word);
//            switch(code)
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_ENERGY:
//            {
//                float v;
//                ParseBlockedFloat(buffer, v);
//                value.SetEnergy(v);
//            }
//                break;
//            case WORD_COLOR:
//            {
//                Math::vec3 v;
//                ParseBlockedVector3f(buffer, v);
//                value.SetColor(v);
//            }
//                break;
//            default:
//                throw Error::LoaderException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
//}
//PUNK_ENGINE_END
