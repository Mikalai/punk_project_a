//#include "../../scene/skin_mesh_node.h"
//#include "parse_functions.h"

//namespace Loader
//{
//    bool ParseSkinMeshNode(Core::Buffer& buffer, Scene::SkinMeshNode* mesh)
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
//                mesh->SetName(value);
//                mesh->SetStorageName(value + L".skin");
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }

//}
