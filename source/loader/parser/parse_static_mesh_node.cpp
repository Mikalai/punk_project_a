//#include "../../scene/module.h"
//#include "parse_functions.h"

//namespace Loader
//{
//    bool ParseStaticMeshNode(Core::Buffer& buffer, Scene::StaticMeshNode* mesh)
//    {
//        CHECK_START(buffer);
//        while (!buffer.IsEnd())
//        {
//            Core::String word = buffer.ReadWord();
//            switch (Parse(word))
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NAME:
//            {
//                Core::String value;
//                ParseBlockedString(buffer, value);
//                mesh->SetName(value);
//                mesh->SetStorageName(value + L".static");
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
//}
