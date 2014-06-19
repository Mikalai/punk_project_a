#include <attributes/animation/module.h>
#include <core/ifactory.h>
#include "parser.h"
#include "parse_rotation_track.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

    bool ParseAnimation(Core::Buffer& buffer, void* object) {

		Attributes::IAnimation* animation = (Attributes::IAnimation*)object;
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);

        Core::String name;

        while (1) {
        
			if (buffer.IsEnd()) {
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
            case WORD_TRACK_VEC3:
            {
				Core::UniquePtr<Attributes::Track<Math::vec3>> track{ nullptr, Core::DestroyObject }; 
				Core::GetFactory()->CreateInstance(Attributes::IID_IVec3Track, (void**)&track);
                parser->Parse(WORD_TRACK_VEC3, buffer, track.get());
                animation->AddTrack(track.get());
            }
                break;
            case WORD_TRACK_QUAT:
            {
				Core::UniquePtr<Attributes::Track<Math::quat>> track{ nullptr, Core::DestroyObject };
				Core::GetFactory()->CreateInstance(Attributes::IID_IQuatTrack, (void**)&track);
                parser->Parse(WORD_TRACK_QUAT, buffer, track.get());
                animation->AddTrack(track.get());
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
	
	PUNK_REGISTER_PARSER(WORD_ACTION, ParseAnimation);
}
PUNK_ENGINE_END
