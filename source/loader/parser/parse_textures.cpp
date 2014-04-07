#include "parser.h"
#include "parse_simple.h"
#include "parse_textures.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseTextures(Core::Buffer& buffer, std::map<Core::String, std::vector<std::array<Math::vec2, 4>>>& value)
    {
        CHECK_START(buffer);

        Core::String name;

        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String s = buffer.ReadWord();

            switch(KeywordCode index = Parse(s))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                ParseBlockedString(buffer, name);
            }
                break;
            case WORD_TEXTURE_COORD:
            {
                ParseVector4Vector2iv(buffer, value[name]);
            }
                break;
            default:
                throw Error::LoaderException(Core::String("Unexpected keyword {0}").arg(Keyword[index].word));
            }
        }
        return true;
    }

}
PUNK_ENGINE_END
