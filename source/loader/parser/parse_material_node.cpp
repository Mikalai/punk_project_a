//#include "../../scene/module.h"
//#include "parse_functions.h"

//namespace IoModule
//{
//    bool ParseMaterialNode(Core::Buffer& buffer, SceneModule::MaterialNode* material)
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
//                material->SetName(value);
//                material->SetStorageName(value + L".material");
//            }
//                break;
//            case WORD_STATIC_MESH_NODE:
//            {
//                std::unique_ptr<SceneModule::StaticMeshNode> node(new SceneModule::StaticMeshNode);
//                ParseStaticMeshNode(buffer, node.get());
//                material->Add(node.release());
//            }
//                break;
//            case WORD_SKIN_MESH_NODE:
//            {
//                std::unique_ptr<SceneModule::SkinMeshNode> node(new SceneModule::SkinMeshNode);
//                ParseSkinMeshNode(buffer, node.get());
//                material->Add(node.release());
//            }
//                break;
//            case WORD_TRANSFORM_NODE:
//            {
//                std::unique_ptr<SceneModule::TransformNode> node(new SceneModule::TransformNode);
//                ParseTransformNode(buffer, node.get());
//                material->Add(node.release());
//            }
//                break;
//            case WORD_MATERIAL_NODE:
//            {
//                std::unique_ptr<SceneModule::MaterialNode> node(new SceneModule::MaterialNode);
//                ParseMaterialNode(buffer, node.get());
//                material->Add(node.release());
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
//}
