#include <attributes/skinning/ibone.h>
#include <math/quat.h>
#include <math/vec3.h>
#include <math/mat4.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseBone(Core::Buffer& buffer, void* object)
    {
		Parser* parser = GetDefaultParser();
		Attributes::IBone* bone = (Attributes::IBone*)object;

        CHECK_START(buffer);
        Core::String name, parent;
        while (1)
        {
            const Core::String word = buffer.ReadWord();
            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                parser->Parse(WORD_STRING, buffer, (void*)&name);
                bone->SetName(name);
            }
                break;
			case WORD_INDEX:
			{
				std::uint32_t index;
				parser->Parse<std::uint32_t>(WORD_UINT32, buffer, index);
				bone->SetIndex(index);
			}
				break;
            case WORD_PARENT:
            {
                std::uint32_t index;
				parser->Parse(WORD_UINT32, buffer, (void*)&index);
                bone->SetParent(index);
            }
                break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                parser->Parse<Math::mat4>(WORD_MATRIX4X4F, buffer, m);
                bone->SetBoneToArmatureMatrix(m);
            }
                break;
            case WORD_LENGTH:
            {
                float l;
                parser->Parse(WORD_FLOAT, buffer, (void*)&l);
                bone->SetLength(l);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_BONE, ParseBone);
}
PUNK_ENGINE_END
