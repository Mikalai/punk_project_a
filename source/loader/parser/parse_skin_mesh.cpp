//#include <attributes/skinning/module.h>
//#include <attributes/geometry/igeometry.h>
//#include "parser.h"
//#include "parse_simple.h"
//#include "parse_skin_mesh.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule
//{
//    bool ParseSkinMesh(Core::Buffer& buffer, Attributes::IGeometry* geometry)
//    {
//        CHECK_START(buffer);
//        while (1)
//        {
//            if (buffer.IsEnd())
//                throw Error::LoaderException(L"Can't parse object");
//
//            Core::String word = buffer.ReadWord();
//
//            KeywordCode code = ParseKeyword(word);
//            switch(code)
//            {
//            case WORD_CLOSE_BRACKET:
//                return true;
//            case WORD_NAME:
//            {
//                Core::String name;
//                ParseBlockedString(buffer, name);
//                geometry->SetName(name);                
//            }
//                break;
//            case WORD_VERTEX_POSITION:
//            {
//                Math::vec3v v;
//                ParseVector3fv(buffer, v);
//                geometry->SetVertexPositions(v);
//            }
//                break;
//            case WORD_NORMALS:
//            {
//                Math::vec3v n;
//                ParseVector3fv(buffer, n);
//                geometry->SetVertexNormals(n);
//            }
//                break;
//            case WORD_ARMATURE_SCHEMA_TEXT:
//            {
//                Core::String name;
//                ParseBlockedString(buffer, name);
//                geometry->SetArmatureSchema(name);
//            }
//                break;
//            case WORD_FACES:
//            {
//                Math::ivec3v f;
//                ParseVector3iv(buffer, f);
//                geometry->SetTriangles(f);
//            }
//                break;
//            case WORD_TEXTURE:
//            {
//				std::vector	<std::array<Math::vec2, 3>> t;
//				int slot = 0;
//                ParseTextures(buffer, slot, t);
//                geometry->SetFaceTextureCoordinates(slot, t);
//            }
//                break;
//           
//            case WORD_WORLD_MATRIX:
//            {
//                Math::mat4 m;
//                ParseBlockedMatrix4x4f(buffer, m);
//                geometry->SetWorldOffset(m);
//            }
//                break;
//            default:
//                throw Error::LoaderException(L"Unexpected keyword " + word);
//            }
//        }
//    }
//}
//PUNK_ENGINE_END
