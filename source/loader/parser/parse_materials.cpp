//#include "../../virtual/data/material.h"
//#include "parse_functions.h"

//namespace Loader
//{
//    bool ParseMaterials(Core::Buffer& buffer, Scene::SceneGraph*)
//    {
//        CHECK_START(buffer);
//        Core::String name;
//        while (1)
//        {
//            Core::String word = buffer.ReadWord();
//            KeywordCode code = Parse(word);
//            switch(code)
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_MATERIAL:
//            {
//                std::unique_ptr<Attributes::Material> m(new Attributes::Material);
//                ParseMaterial(buffer, m.get());
//                m.release();
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
//}
