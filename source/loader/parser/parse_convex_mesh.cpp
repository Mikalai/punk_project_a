#include "parser.h"
#include "parse_simple.h"
#include <math/convex_shape_mesh.h>

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseConvexMesh(Core::Buffer& buffer, Math::ConvexShapeMesh& mesh)
    {
        CHECK_START(buffer);

        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse convex mesh");

            Core::String s = buffer.ReadWord();
            KeywordCode index = Parse(s);
            switch (index)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_VERTEX_POSITION:
            {
                std::vector<Math::vec3> p;
                ParseVector3fv(buffer, p);
                mesh.SetPoints(&p[0], p.size());
            }
                break;
            case WORD_FACES:
            {
                std::vector<Math::ivec3> f;
                ParseVector3iv(buffer, f);
                mesh.SetFaces(&f[0], f.size());
            }
                break;
            case WORD_FACE_NORMALS:
            {
                std::vector<Math::vec3> n;
                ParseVector3fv(buffer, n);
                mesh.SetNormals(&n[0], n.size());
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected word " + s);
            }
        }
    }
}
PUNK_ENGINE_END
