#include <attributes/skinning/module.h>
#include "parser.h"
#include "parse_simple.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseBone(Core::Buffer& buffer, Attributes::Bone* bone)
    {
        CHECK_START(buffer);
        Core::String name, parent;
        while (1)
        {
            const Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                bone->SetName(name);
            }
                break;
            case WORD_PARENT:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                bone->SetParentName(name);
            }
                break;
            case WORD_LOCAL_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                bone->SetLocalMatrix(m);
            }
                break;
            case WORD_BONE_MATRIX:
            {
                Math::mat4 m;
                ParseBlockedMatrix4x4f(buffer, m);
                //bone->SetBoneMatrix(m);
            }
                break;
            case WORD_LENGTH:
            {
                float l;
                ParseBlockedFloat(buffer, l);
                bone->SetLength(l);
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
