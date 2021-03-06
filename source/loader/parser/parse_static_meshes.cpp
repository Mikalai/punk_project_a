//#include "../../virtual/data/static_geometry.h"
//#include "parse_functions.h"

//namespace IoModule
//{
//    bool ParseStaticMeshes(Core::Buffer& buffer)
//    {
//        CHECK_START(buffer);

//        while (1)
//        {
//            if (buffer.IsEnd())
//                throw System::PunkInvalidArgumentException(L"Can't parse object");

//            Core::String word = buffer.ReadWord();
//            KeywordCode index;
//            switch(index = ParseKeyword(word))
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_STATIC_MESH:
//            {
//                std::unique_ptr<Attributes::StaticGeometry> mesh(new Attributes::StaticGeometry);
//                ParseStaticMesh(buffer, mesh.get());
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
