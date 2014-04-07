#include "parser.h"
#include "parse_simple.h"
#include <ai/module.h>

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseNaviMesh(Core::Buffer &buffer, AI::NaviMesh* value)
    {
        CHECK_START(buffer);
        Core::String name;
        while (1)
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
            {
                return true;
            }
            case WORD_WORLD_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                value->SetTransform(m);
            }
            break;
            case WORD_VERTEX_POSITION:
            {
                AI::NaviMesh::Points v;
                ParseVector3fv(buffer, v);
                value->SetPoints(v);
            }
            break;
            case WORD_NORMALS:
            {
                AI::NaviMesh::Normals v;
                ParseVector3fv(buffer, v);
                value->SetNormals(v);
            }
            break;
            case WORD_FACES:
            {
                AI::NaviMesh::Faces f;
                ParseVector3iv(buffer, f);
                value->SetFaces(f);
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
PUNK_ENGINE_END
