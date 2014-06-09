#include <math/mat4.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <attributes/geometry/igeometry.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	bool ParseTextureCoordinates(Core::Buffer& buffer, void* object)
	{
		std::vector<std::vector<std::array<Math::vec2, 3>>>* coords = (std::vector<std::vector<std::array<Math::vec2, 3>>>*)object;
		Parser* parser = GetDefaultParser();
		int index = 0;

		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				throw Error::LoaderException(L"Can't parse object");

			Core::String word = buffer.ReadWord();

			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
			{
				Core::String name;
				parser->Parse(WORD_STRING, buffer, name);
				index = name.ToInt32();
				coords->resize(index + 1);
			}
				break;
			case WORD_TEXTURE_COORD:
			{
				std::vector<std::array<Math::vec2, 3>> v;
				parser->Parse(WORD_VEC3VEC2VF, buffer, &v);
				(*coords)[index] = v;
			}
				break;
			default:
				throw Error::LoaderException(L"Unexpected keyword " + word);
			}
		}
	}

	PUNK_REGISTER_PARSER(WORD_TEXTURE_COORD, ParseTextureCoordinates);
}
PUNK_ENGINE_END
