#include <attributes/module.h>
#include "parser.h"
#include "parse_animation.h"
#include "parse_simple.h"
#include "parse_action.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseAction(Core::Buffer& buffer, Attributes::Action* action)
    {
        CHECK_START(buffer);

        Core::String name;

        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse action");

            const Core::String word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
                action->SetName(value);
            }
                break;
            case WORD_TIMING:
            {
                CHECK_START(buffer);
                action->SetStartFrame(buffer.ReadWord().ToInt32());
                action->SetEndFrame(buffer.ReadWord().ToInt32());
                if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)
                    throw Error::LoaderException(L"Can't parse action timing");
            }
                break;
            case WORD_BONE_ANIMATION:
            {
                std::unique_ptr<Attributes::BoneAnimation> animation(new Attributes::BoneAnimation);
                ParseAnimation(buffer, animation.get());
                action->Add(animation.release());
            }
                break;
            case WORD_OBJECT_ANIMATION:
            {
                std::unique_ptr<Attributes::ObjectAnimation> animation(new Attributes::ObjectAnimation);
                ParseAnimation(buffer, animation.get());
                action->Add(animation.release());
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }

    bool ParseActions(Core::Buffer& buffer)
    {
        CHECK_START(buffer);

        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();
            KeywordCode index;
            switch(index = Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

}
PUNK_ENGINE_END
