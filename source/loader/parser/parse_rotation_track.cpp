#include "parser.h"
#include "parse_rotation_track.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseRotationTrack(Core::Buffer& buffer, Attributes::AnimationTrack<Math::quat>& value)
    {
        CHECK_START(buffer);
        while (1)
        {
            Core::String word = buffer.ReadWord();

            if (word == Keyword[WORD_CLOSE_BRACKET].word)
                return true;

            int frame = word.ToInt32();
            float w = buffer.ReadWord().ToFloat();
            float x = buffer.ReadWord().ToFloat();
            float y = buffer.ReadWord().ToFloat();
            float z = buffer.ReadWord().ToFloat();

            Math::quat v;
            v.Set(w,x,y,z);

            value.AddKey(frame, v);
        }
        throw Error::LoaderException(L"Unable to parse rotation track");
    }
}
PUNK_ENGINE_END
