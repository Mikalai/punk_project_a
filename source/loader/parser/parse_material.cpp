#include <core/ifactory.h>
#include <attributes/material/imaterial.h>
#include <attributes/material/itexture_slot.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	bool ParseMaterial(Core::Buffer& buffer, void* object)
	{
		Parser* parser = GetDefaultParser();
		Attributes::IMaterial* mat = (Attributes::IMaterial*)(object);

		CHECK_START(buffer);

		Core::String name;
		while (1)
		{
			Core::String word = buffer.ReadWord();
			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
			{
				Core::String value;
				parser->Parse(WORD_STRING, buffer, &value);
				mat->SetName(value);
			}
				break;
			case WORD_ALPHA:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetAlpha(value);
			}
				break;
			case WORD_AMBIENT:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, value);
				mat->SetAmbient(value);
			}
				break;
			case WORD_DARKNESS:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetDarkness(value);
			}
				break;
			case WORD_DIFFUSE_COLOR:
			{
				Math::vec3 value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetDiffuseColor(Math::vec4(value, mat->GetAlpha()));
			}
				break;
			case WORD_DIFFUSE_FRESNEL:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetDiffuseFresnel(value);
			}
				break;
			case WORD_DIFFUSE_FRESNEL_FACTOR:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetDiffuseFresnelFactor(value);
			}
				break;
			case WORD_DIFFUSE_INTENSITY:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetDiffuseIntensity(value);
			}
				break;
			case WORD_EMIT:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetEmit(value);
			}
				break;
			case WORD_MIRROR_COLOR:
			{
				Math::vec3 value;
				parser->Parse(WORD_VEC3F, buffer, &value);
				mat->SetMirrorColor(value);
			}
				break;
			case WORD_ROUGHNESS:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetRoughness(value);
			}
				break;
			case WORD_SPECULAR_ALPHA:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetSpecularAlpha(value);
			}
				break;
			case WORD_SPECULAR_COLOR:
			{
				Math::vec3 value;
				parser->Parse(WORD_VEC3F, buffer, &value);
				mat->SetSpecularColor(Math::vec4(value, mat->GetSpecularAlpha()));
			}
				break;
			case WORD_SPECULAR_HARDNESS:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetSpecularFactor(value);
			}
				break;
			case WORD_SPECULAR_INTENSITY:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetSpecularIntensity(value);
			}
				break;
			case WORD_SPECULAR_IOR:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetSpecularIndexOfRefraction(value);
			}
				break;
			case WORD_SPECULAR_SLOPE:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetSpecularSlope(value);
			}
				break;
			case WORD_TRANSLUCENCY:
			{
				float value;
				parser->Parse(WORD_FLOAT, buffer, &value);
				mat->SetTranslucency(value);
			}
				break;
			case WORD_DIFFUSE_TEXTURE_SLOT:
			{
				Attributes::IDiffuseTextureSlot* slot{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_IDiffuseTextureSlot, (void**)&slot);
				parser->Parse(WORD_DIFFUSE_TEXTURE_SLOT, buffer, slot);
				mat->SetDiffuseTextureSlot(slot);
			}
				break;
			case WORD_NORMAL_TEXTURE_SLOT:
			{
				Attributes::INormalTextureSlot* slot{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_INormalTextureSlot, (void**)&slot);
				parser->Parse(WORD_NORMAL_TEXTURE_SLOT, buffer, slot);
				mat->SetNormalTextureSlot(slot);
			}
				break;
			case WORD_SPECULAR_TEXTURE_SLOT:
			{
				Attributes::ISpecularIntensityTextureSlot* slot{ nullptr };
				Core::GetFactory()->CreateInstance(Attributes::IID_ISpecularIntensityTextureSlot, (void**)&slot);
				parser->Parse(WORD_SPECULAR_TEXTURE_SLOT, buffer, slot);
				mat->SetSpecularTextureSlot(slot);
			}
				break;
			default:
				throw Error::LoaderException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	//    bool ParseMaterials(Core::Buffer& buffer, SceneModule::Scene*)
	//    {
	//        CHECK_START(buffer);
	//        Core::String name;
	//        while (1)
	//        {
	//            Core::String word = buffer.ReadWord();
	//            KeywordCode code = ParseKeyword(word);
	//            switch(code)
	//            {
	//            case WORD_CLOSE_BRACKET:
	//                return true;
	//            case WORD_MATERIAL:
	//            {
	//                std::unique_ptr<Attributes::Material> m(new Attributes::Material);
	//                ParseMaterial(buffer, m.get());
	//                m.release();
	//            }
	//                break;
	//            default:
	//                throw Error::LoaderException(L"Unexpected keyword " + word);
	//            }
	//        }
	//        return false;
	//    }
}
PUNK_ENGINE_END
