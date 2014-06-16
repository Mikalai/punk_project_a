//#include "parse_functions.h"
//#include "../../scene/module.h"

//namespace IoModule
//{
//    bool ParseSunNode(Core::Buffer &buffer, SceneModule::SunNode &value)
//    {
//        CHECK_START(buffer);
//        while (1)
//        {
//            const Core::String word = buffer.ReadWord();
//            KeywordCode code = ParseKeyword(word);
//            switch(code)
//            {
//            case WORD_CLOSE_BRACKET:
//            return true;
//            case WORD_NAME:
//            {
//                Core::String name;
//                ParseBlockedString(buffer, name);
//                value.SetName(name);
//                value.SetStorageName(name + L".sun");
//            }
//            break;
//            case WORD_TRANSFORM_NODE:
//            {
//                std::unique_ptr<SceneModule::TransformNode> node(new SceneModule::TransformNode);
//                ParseTransformNode(buffer, node.get());
//                value.Add(node.release());
//            }
//            break;
//            case WORD_MATERIAL_NODE:
//            {
//                std::unique_ptr<SceneModule::MaterialNode> node(new SceneModule::MaterialNode);
//                ParseMaterialNode(buffer, node.get());
//                value.Add(node.release());
//            }
//            break;
//            default:
//            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
//            }
//        }
//        return false;
//    }
//}
