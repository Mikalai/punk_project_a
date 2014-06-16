//#include <attributes/skinning/bone.h>
//#include "parser.h"

//PUNK_ENGINE_BEGIN
//namespace IoModule
//{
//    bool ParseBoneNode(Core::Buffer& buffer, SceneModule::BoneNode* bone)
//    {
//        CHECK_START(buffer);
//        while (!buffer.IsEnd())
//        {
//            Core::String word = buffer.ReadWord();
//            switch (ParseKeyword(word))
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NAME:
//            {
//                Core::String value;
//                ParseBlockedString(buffer, value);
//                bone->SetName(value);
//                bone->SetStorageName(value);
//            }
//                break;
//            case WORD_TRANSFORM_NODE:
//            {
//                std::unique_ptr<SceneModule::TransformNode> node(new SceneModule::TransformNode);
//                ParseTransformNode(buffer, node.get());
//                bone->Add(node.release());
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }

//}
//PUNK_ENGINE_END
