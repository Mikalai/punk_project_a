//#include "parse_functions.h"
//#include "../../scene/module.h"

//PUNK_ENGINE_BEGIN
//namespace Loader {
//    bool ParsePathNode(Core::Buffer &buffer, Scene::PathNode &value)
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
//                value.SetStorageName(name + L".path");
//            }
//            break;
//            default:
//            return (out_error() << L"Unexpected keyword " << word << std::endl, false);
//            }
//        }
//        return false;
//    }
//}
