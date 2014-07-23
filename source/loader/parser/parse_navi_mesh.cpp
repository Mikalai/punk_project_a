#include <attributes/ai/module.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	bool ParseNaviMesh(Core::Buffer &buffer, void* object)
	{
		Attributes::INaviMesh* value = (Attributes::INaviMesh*)object;
		Parser* parser = GetDefaultParser();

		CHECK_START(buffer);
		Core::String name;
		while (1)
		{
			Core::String word = buffer.ReadWord();
			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_CLOSE_BRACKET:
			{
				return true;
			}
			case WORD_WORLD_MATRIX:
			{
				Math::mat4 m;
				parser->Parse<Math::mat4>(WORD_MATRIX4X4F, buffer, m);
				value->SetTransform(m);
			}
				break;
			case WORD_VERTEX_POSITION:
			{
				Math::vec3v v;
				parser->Parse(WORD_VEC3FV, buffer, &v);
				value->SetVertexPositions(v.data(), (std::uint32_t)v.size());
			}
				break;
			case WORD_NORMALS:
			{
				Math::vec3v v;
				parser->Parse(WORD_VEC3FV, buffer, v);
				value->SetVertexNormals(v.data(), (std::uint32_t)v.size());
			}
				break;
			case WORD_FACES:
			{
				Math::ivec3v f;
				parser->Parse(WORD_VEC3IV, buffer, f);
				value->SetTriangles(f.data(), (std::uint32_t)f.size());
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
