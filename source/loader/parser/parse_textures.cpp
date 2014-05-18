//#include "parser.h"
//#include "parse_textures.h"
//
//PUNK_ENGINE_BEGIN
//namespace Loader
//{
//    bool ParseTextures(Core::Buffer& buffer, int& slot, std::vector<std::array<Math::vec2, 3>>& value)
//    {
//		Parser* parser = GetDefaultParser();
//        CHECK_START(buffer);
//
//        Core::String name;
//
//        while (1)
//        {
//            if (buffer.IsEnd())
//                throw Error::LoaderException(L"Can't parse object");
//
//            Core::String s = buffer.ReadWord();
//
//            switch(KeywordCode index = ParseKeyword(s))
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NAME:
//            {
//                parser->Parse<Core::String>(WORD_STRING, buffer, name);
//            }
//                break;
//            case WORD_TEXTURE_COORD:
//            {
//                parserParseVector3Vector2fv(buffer, value);
//            }
//                break;
//            default:
//                throw Error::LoaderException(Core::String("Unexpected keyword {0}").arg(Keyword[index].word));
//            }
//        }
//        return true;
//    }
//
//}
//PUNK_ENGINE_END
