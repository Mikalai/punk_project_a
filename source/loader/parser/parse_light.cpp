#include <attributes/light/idirectional_light.h>
#include <attributes/light/ipoint_light.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    bool ParseDirectionalLight(Core::Buffer& buffer, void* object)
    {
		Parser* parser = GetDefaultParser();
		Attributes::IDirectionalLight* value = (Attributes::IDirectionalLight*)object;
        CHECK_START(buffer);
        while (1)
        {
            const Core::String word = buffer.ReadWord();
            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_ENERGY:
            {
                float v;
                parser->Parse(WORD_FLOAT, buffer, &v);
                value->SetEnergy(v);
            }
                break;
            case WORD_COLOR:
            {
                Math::vec3 v;
                parser->Parse(WORD_VEC3F, buffer, &v);
                value->SetDiffuseColor(v);
            }
                break;
            case WORD_DIRECTION:
            {
                Math::vec3 v;
                parser->Parse(WORD_VEC3F, buffer, v);
                value->SetDirection(v);
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	bool ParsePointLight(Core::Buffer& buffer, void* object)
	{
		Parser* parser = GetDefaultParser();
		Attributes::IPointLight* light = (Attributes::IPointLight*)object;

		CHECK_START(buffer);
		
		while (!buffer.IsEnd())
		{
			Core::String word = buffer.ReadWord();
			switch (ParseKeyword(word))
			{
			case WORD_CLOSE_BRACKET:				
				return true;
			case WORD_NAME:
			{
				Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				light->SetName(name);
			}
				break;
			case WORD_COLOR:
			{
				Math::vec3 color;
				parser->Parse(WORD_VEC3F, buffer, &color);
				light->SetDiffuseColor(color);
			}
				break;
			case WORD_DISTANCE:
			{
				float dst;
				parser->Parse(WORD_FLOAT, buffer, &dst);
				light->SetDistance(dst);
			}
				break;
			case WORD_ENERGY:
			{
				float energy;
				parser->Parse(WORD_FLOAT, buffer, &energy);
				light->SetEnergy(energy);
			}
				break;
			case WORD_LINEAR_ATTENUATION:
			{
				float v;
				parser->Parse(WORD_FLOAT, buffer, &v);
				light->SetLinearAttenuation(v);
			}
				break;
			case WORD_QUADRATIC_ATTENUATION:
			{
				float v;
				parser->Parse(WORD_FLOAT, buffer, &v);
				light->SetQuadraticAttenuation(v);
			}
				break;
			default:
				throw Error::LoaderException(L"Unexpected keyword " + word);
			}
		}
		return true;
	}

	PUNK_REGISTER_PARSER(WORD_DIRECTIONAL_LIGHT, ParseDirectionalLight);
	PUNK_REGISTER_PARSER(WORD_POINT_LIGHT, ParsePointLight);
}
PUNK_ENGINE_END
