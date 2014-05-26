#include <attributes/material/itexture_slot.h>
#include <attributes/material/idiffuse_texture_slot.h>
#include <attributes/material/inormal_texture_slot.h>
#include <attributes/material/ispecular_intensity_texture_slot.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	template<class T>
    bool ParseTextureSlot(Core::Buffer& buffer, void* object)
    {
		Parser* parser = GetDefaultParser();
		T* value = (T*)object;

        CHECK_START(buffer);
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(ParseKeyword(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_SCALE:
            {
                Math::vec3 v;
				parser->Parse(WORD_VEC3F, buffer, v);
                value->SetScale(v);
            }
            break;
            case WORD_IMAGE:
            {
                Core::String v;
                parser->Parse(WORD_STRING, buffer, v);
                value->SetFilename(v);
            }
            break;
            case WORD_FACTOR:
            {
                float v;
                parser->Parse(WORD_FLOAT, buffer, v);                
                value->SetFactor(v);
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_DIFFUSE_TEXTURE_SLOT, ParseTextureSlot<Attributes::IDiffuseTextureSlot>);
	PUNK_REGISTER_PARSER(WORD_NORMAL_TEXTURE_SLOT, ParseTextureSlot<Attributes::INormalTextureSlot>);
	PUNK_REGISTER_PARSER(WORD_SPECULAR_TEXTURE_SLOT, ParseTextureSlot<Attributes::ISpecularIntensityTextureSlot>);

}
PUNK_ENGINE_END
