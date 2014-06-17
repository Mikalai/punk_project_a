#include <attributes/animation/module.h>
#include <core/ifactory.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseRotationTrack(Core::Buffer& buffer, void* object)
    {
		Attributes::Track<Math::quat>* value = (Attributes::Track<Math::quat>*)object;
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

			Core::UniquePtr<Attributes::KeyFrame<Math::quat>> key_frame{ nullptr, Core::DestroyObject };
			Core::GetFactory()->CreateInstance(Attributes::IID_IQuatKeyFrame, (void**)&key_frame);
			key_frame->SetFrame(frame);
			key_frame->Key(v);
			value->AddKeyFrame(key_frame.get());
        }
        throw Error::LoaderException(L"Unable to parse rotation track");
    }

	PUNK_REGISTER_PARSER(WORD_ROTATION_TRACK, ParseRotationTrack);
}
PUNK_ENGINE_END
