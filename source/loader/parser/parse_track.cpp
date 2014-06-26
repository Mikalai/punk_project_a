#include <attributes/module.h>
#include <system/factory/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	template<class T> struct KeyReader;
	
	template<>
	struct KeyReader<Math::vec3> {
		static Attributes::KeyFrame<Math::vec3>* Read(Core::Buffer& buffer) {
            auto keyframe = System::CreateInstancePtr<Attributes::KeyFrame<Math::vec3>>(Attributes::IID_IVec3KeyFrame);
			auto word = buffer.ReadWord();
			if (GetKeyword(WORD_CLOSE_BRACKET) == word)
				return nullptr;
			int frame = word.ToInt32();
			Math::vec3 value;
			value[0] = buffer.ReadWord().ToFloat();
			value[1] = buffer.ReadWord().ToFloat();
			value[2] = buffer.ReadWord().ToFloat();
			keyframe->SetFrame(frame);
			keyframe->Key(value);
            return keyframe.release();
		}

		static Attributes::KeyFrame<Math::vec3>* CreateKeyFrame() {
			
		}
	};

	template<>
	struct KeyReader<Math::quat> {
		static Attributes::KeyFrame<Math::quat>* Read(Core::Buffer& buffer) {
            auto keyframe = System::CreateInstancePtr<Attributes::KeyFrame<Math::quat>>(Attributes::IID_IQuatKeyFrame);
			auto word = buffer.ReadWord();
			if (GetKeyword(WORD_CLOSE_BRACKET) == word)
				return nullptr;
			int frame = word.ToInt32();
			Math::quat value;
			value[0] = buffer.ReadWord().ToFloat();
			value[1] = buffer.ReadWord().ToFloat();
			value[2] = buffer.ReadWord().ToFloat();
			value[3] = buffer.ReadWord().ToFloat();
			keyframe->SetFrame(frame);
			keyframe->Key(value);
            return keyframe.release();
		}

		static Attributes::KeyFrame<Math::vec3>* CreateKeyFrame() {

		}
	};

	template<class T>
    bool ParseTrack(Core::Buffer& buffer, void* object)
    {
        CHECK_START(buffer);
		Parser* parser = GetDefaultParser();
		Attributes::Track<T>* track = (Attributes::Track<T>*)object;
        Core::String name;

        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse action");

            Core::String word = buffer.ReadWord();
            KeywordCode index;
            switch(index = ParseKeyword(word))
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String value;
                parser->Parse<Core::String>(WORD_STRING, buffer, value);
                track->SetName(value);
            }
                break;
            case WORD_KEYS:
            {
				word = buffer.ReadWord();
				while (true) {
					Core::Pointer<Attributes::KeyFrame<T>> keyframe{ KeyReader<T>::Read(buffer), Core::DestroyObject };
					if (!keyframe.get())
						break;
					track->AddKeyFrame(keyframe.get());
				}
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }

	PUNK_REGISTER_PARSER(WORD_TRACK_VEC3, ParseTrack<Math::vec3>);
	PUNK_REGISTER_PARSER(WORD_TRACK_QUAT, ParseTrack<Math::quat>);

}
PUNK_ENGINE_END
