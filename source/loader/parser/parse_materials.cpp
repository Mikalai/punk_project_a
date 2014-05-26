//#include "../../virtual/data/material.h"
//#include "parse_functions.h"

//namespace IoModule
//{
//    bool ParseMaterials(Core::Buffer& buffer, SceneModule::Scene*)
//    {
//        CHECK_START(buffer);
//        Core::String name;
//        while (1)
//        {
//            Core::String word = buffer.ReadWord();
//            KeywordCode code = ParseKeyword(word);
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
