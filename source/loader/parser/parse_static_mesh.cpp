#include <attributes/data/static_geometry.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_static_mesh.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseStaticMesh(Core::Buffer& buffer, Attributes::StaticGeometry* geometry)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                geometry->SetName(name);                
            }
                break;
            case WORD_VERTEX_POSITION:
            {
                Attributes::StaticGeometry::Vertices v;
                ParseVector3fv(buffer, v);
                geometry->SetVertices(v);
            }
                break;
            case WORD_NORMALS:
            {
                Attributes::StaticGeometry::Normals n;
                ParseVector3fv(buffer, n);
                geometry->SetNormals(n);
            }
                break;
            case WORD_FACES:
            {
                Attributes::StaticGeometry::Faces f;
                ParseVector3iv(buffer, f);
                geometry->SetFaces(f);
            }
                break;
            case WORD_TEXTURE:
            {
                Attributes::StaticGeometry::TextureMeshes t;
                ParseTextures(buffer, t);
                geometry->SetTextureMeshes(t);
            }
                break;
            case WORD_WORLD_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                geometry->SetWorldOffset(m);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }
}
PUNK_ENGINE_END
