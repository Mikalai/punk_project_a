#include <attributes/animation/module.h>
#include "parser.h"
#include "parse_rotation_track.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseAnimation(Core::Buffer& buffer, void* object)
    {
		Attributes::IAnimation* animation = (Attributes::IAnimation*)object;
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);

        Core::String name;

        while (1)
        {
            if (buffer.IsEnd())
            {
                throw Error::LoaderException(L"Can't parse object");
            }

            const Core::String word = buffer.ReadWord();
            KeywordCode index = ParseKeyword(word);
            switch(index)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                parser->Parse(WORD_STRING, buffer, name);
                animation->SetName(name);
            }
                break;
            case WORD_POSITION_TRACK:
            {
                Attributes::AnimationTrack<Math::vec3> track;
                parser->Parse(WORD_POSITION_TRACK, buffer, &track);
                animation->SetPositionTrack(track);
            }
                break;
            case WORD_ROTATION_TRACK:
            {
                Attributes::AnimationTrack<Math::quat> track;
                parser->Parse(WORD_ROTATION_TRACK, buffer, track);
                animation->SetRotationTrack(track);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
	
	PUNK_REGISTER_PARSER(WORD_OBJECT_ANIMATION, ParseAnimation);
}
PUNK_ENGINE_END
