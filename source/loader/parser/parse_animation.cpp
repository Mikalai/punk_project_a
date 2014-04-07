#include <attributes/animation/module.h>
#include "parse_simple.h"
#include "parser.h"
#include "parse_animation.h"
#include "parse_position_track.h"
#include "parse_rotation_track.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseAnimation(Core::Buffer& buffer, Attributes::Animation* animation)
    {
        CHECK_START(buffer);

        Core::String name;

        while (1)
        {
            if (buffer.IsEnd())
            {
                throw Error::LoaderException(L"Can't parse object");
            }

            const Core::String word = buffer.ReadWord();
            KeywordCode index = Parse(word);
            switch(index)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                animation->SetName(name);
            }
                break;
            case WORD_POSITION_TRACK:
            {
                Attributes::AnimationTrack<Math::vec3> track;
                ParsePositionTrack(buffer, track);
                animation->SetPositionTrack(track);
            }
                break;
            case WORD_ROTATION_TRACK:
            {
                Attributes::AnimationTrack<Math::quat> track;
                ParseRotationTrack(buffer, track);
                animation->SetRotationTrack(track);
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
