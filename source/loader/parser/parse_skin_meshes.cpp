//#include "../../virtual/skinning/module.h"
//#include "../../virtual/data/skin_geometry.h"

//#include "parse_functions.h"

//namespace Loader
//{
//    bool ParseSkinMeshes(Core::Buffer& buffer)
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
//            case WORD_SKIN_MESH:
//            {
//                std::unique_ptr<Attributes::SkinGeometry> mesh(new Attributes::SkinGeometry);
//                ParseSkinMesh(buffer, mesh.get());
//                mesh.release();
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return false;
//    }
//}
