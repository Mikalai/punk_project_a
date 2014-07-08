//#include <system/factory/module.h>
//#include <attributes/animation/module.h>
//#include "parser.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule
//{
//    bool ParsePositionTrack(Core::Buffer& buffer, void* object)
//    {
//		Attributes::Track<Math::vec3>* value = (Attributes::Track<Math::vec3>*)object;
//		Parser* parser = GetDefaultParser();
//        CHECK_START(buffer);
//        while (1)
//        {
//            Core::String word = buffer.ReadWord();
//
//            if (word == Keyword[WORD_CLOSE_BRACKET].word)
//                return true;
//
//            int frame = word.ToInt32();
//            float x = buffer.ReadWord().ToFloat();
//            float y = buffer.ReadWord().ToFloat();
//            float z = buffer.ReadWord().ToFloat();
//
//            Math::vec3 v;
//            v.Set(x,y,z);
//
//			Core::Pointer<Attributes::KeyFrame<Math::vec3>> key_frame{ nullptr, Core::DestroyObject };
//			Core::GetFactory()->CreateInstance(Attributes::IID_IVec3KeyFrame, (void**)&key_frame);
//			key_frame->SetFrame(frame);
//			key_frame->Key(v);
//            value->AddKeyFrame(key_frame.get());
//        }
//        throw Error::LoaderException(L"Unable to parse position track");
//    }
//
//	PUNK_REGISTER_PARSER(WORD_POSITION_TRACK, ParsePositionTrack);
//}
//PUNK_ENGINE_END
