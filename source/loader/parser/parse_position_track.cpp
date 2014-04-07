#include "parser.h"
#include "parse_position_track.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParsePositionTrack(Core::Buffer& buffer, Attributes::AnimationTrack<Math::vec3>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int frame = word.ToInt32();
            float x = buffer.ReadWord().ToFloat();
            float y = buffer.ReadWord().ToFloat();
            float z = buffer.ReadWord().ToFloat();

            Math::vec3 v;
            v.Set(x,y,z);

            value.AddKey(frame, v);
        }
        throw Error::LoaderException(L"Unable to parse position track");
    }
}
PUNK_ENGINE_END
