//#include "../../scene/module.h"
//#include "parse_functions.h"

//namespace IoModule
//{
//    bool ParseArmatureNode(Core::Buffer& buffer, SceneModule::ArmatureNode* armature_node)
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
//                armature_node->SetName(value);
//                armature_node->SetStorageName(value + L".armature");
//            }
//                break;
//            case WORD_MATERIAL_NODE:
//            {
//                std::unique_ptr<SceneModule::MaterialNode> node(new SceneModule::MaterialNode);
//                ParseMaterialNode(buffer, node.get());
//                armature_node->Add(node.release());
//            }
//                break;
//            case WORD_BONE_NODE:
//            {
//                std::unique_ptr<SceneModule::BoneNode> node(new SceneModule::BoneNode);
//                ParseBoneNode(buffer, node.get());
//                armature_node->Add(node.release());
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }

//}
