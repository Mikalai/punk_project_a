#include <attributes/animation/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseRotationTrack(Core::Buffer& buffer, void* object)
    {
		Attributes::AnimationTrack<Math::quat>* value = (Attributes::AnimationTrack<Math::quat>*)object;
		Parser* parser = GetDefaultParser();

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

            value->AddKey(frame, v);
        }
        throw Error::LoaderException(L"Unable to parse rotation track");
    }

	PUNK_REGISTER_PARSER(WORD_ROTATION_TRACK, ParseRotationTrack);
}
PUNK_ENGINE_END
