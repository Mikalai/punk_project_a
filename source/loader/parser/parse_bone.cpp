#include <attributes/skinning/ibone.h>
#include <math/quat.h>
#include <math/vec3.h>
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
            case WORD_PARENT:
            {
                std::uint32_t index;
				parser->Parse(WORD_UINT32, buffer, (void*)&index);
                bone->SetParent(index);
            }
                break;
            case WORD_POSITION:
            {
                Math::vec3 v;
                parser->Parse(WORD_VEC3F, buffer, (void*)&v);
                bone->SetRestPosition(v);
            }
                break;
			case WORD_ROTATION:
			{
				Math::quat q;
				parser->Parse(WORD_QUAT, buffer, (void*)&q);
				bone->SetRestRotation(q);
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
