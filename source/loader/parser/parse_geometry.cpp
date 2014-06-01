#include <math/mat4.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <attributes/geometry/igeometry.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseGeometry(Core::Buffer& buffer, void* object)
    {
		Attributes::IGeometry* geometry = (Attributes::IGeometry*)object;
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                parser->Parse(WORD_STRING, buffer, name);
                geometry->SetName(name);                
            }
                break;
            case WORD_VERTEX_POSITION:
            {
                Math::vec3v v;
                parser->Parse(WORD_VEC3FV, buffer, v);
                geometry->SetVertexPositions(v);
            }
                break;
            case WORD_NORMALS:
            {
                Math::vec3v n;
                parser->Parse(WORD_VEC3FV, buffer, n);
                geometry->SetVertexNormals(n);
            }
                break;
            case WORD_FACES:
            {
                Math::ivec3v f;
				parser->Parse(WORD_VEC3IV, buffer, f);
                geometry->SetTriangles(f);
            }
                break;
            case WORD_TEXTURE:
            {
                std::vector<std::array<Math::vec2, 3>> t;
                parser->Parse(WORD_TEXTURE, buffer, t);
                geometry->SetFaceTextureCoordinates(0, t);
            }
                break;
			case WORD_BONES_WEIGHTS:
			{								
				std::vector<std::vector<std::pair<int, float>>> b;
				parser->Parse(WORD_BONES_WEIGHTS, buffer, (void*)&b);
				geometry->SetVertexBonesWeights(b);
			}
				break;
			case WORD_WORLD_MATRIX:
			{
				Math::mat4 m;
				parser->Parse(WORD_MATRIX4X4F, buffer, m);				
			}
				break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }

	PUNK_REGISTER_PARSER(WORD_STATIC_MESH, ParseGeometry);
	PUNK_REGISTER_PARSER(WORD_SKIN_MESH, ParseGeometry);
}
PUNK_ENGINE_END
