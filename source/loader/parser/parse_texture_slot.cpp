#include <attributes/data/texture_slot.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseTextureSlot(Core::Buffer& buffer, Attributes::TextureSlot& value)
    {
        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_SCALE:
            {
                Math::vec3 v;
                ParseBlockedVector3f(buffer, v);
                value.SetScale(v);
            }
            break;
            case WORD_IMAGE:
            {
                Core::String v;
                ParseBlockedString(buffer, v);
                value.SetFilename(v);
            }
            break;
            case WORD_SPECULAR_INTENSITY_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsSpecularIntensityMapSlot(true);
                value.SetSpecularIntensityFactor(v);
            }
            break;
            case WORD_DIFFUSE_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsDiffuseMapSlot(true);
                value.SetDiffuseFactor(v);
            }
            break;
            case  WORD_NORMAL_MAP:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                value.MarkAsNormalMapSlot(true);
                value.SetNormalFactor(v);
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
