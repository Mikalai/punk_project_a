#include <attributes/data/material.h>
#include <attributes/data/texture_slot.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_texture_slot.h"
#include "parse_material.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseMaterial(Core::Buffer& buffer, Attributes::Material* mat)
    {
        CHECK_START(buffer);
        Core::String name;
        while (1)
        {
            Core::String word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_NAME:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
                mat->SetName(value);                
            }
            break;
            case WORD_ALPHA:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetAlpha(value);
            }
            break;
            case WORD_AMBIENT:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetAmbient(value);
            }
            break;
            case WORD_DARKNESS:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetDarkness(value);
            }
            break;
            case WORD_DIFFUSE_COLOR:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                mat->SetDiffuseColor(Math::vec4(value, mat->GetAlpha()));
            }
            break;
            case WORD_DIFFUSE_FRESNEL:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetDiffuseFresnel(value);
            }
            break;
            case WORD_DIFFUSE_FRESNEL_FACTOR:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetDiffuseFresnelFactor(value);
            }
            break;
            case WORD_DIFFUSE_INTENSITY:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetDiffuseIntensity(value);
            }
            break;
            case WORD_EMIT:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetEmit(value);
            }
            break;
            case WORD_MIRROR_COLOR:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                mat->SetMirrorColor(value);
            }
            break;
            case WORD_ROUGHNESS:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetRoughness(value);
            }
            break;
            case WORD_SPECULAR_ALPHA:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetSpecularAlpha(value);
            }
            break;
            case WORD_SPECULAR_COLOR:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                mat->SetSpecularColor(Math::vec4(value, mat->GetSpecularAlpha()));
            }
            break;
            case WORD_SPECULAR_HARDNESS:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetSpecularFactor(value);
            }
            break;
            case WORD_SPECULAR_INTENSITY:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetSpecularIntensity(value);
            }
            break;
            case WORD_SPECULAR_IOR:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetSpecularIndexOfRefraction(value);
            }
            break;
            case WORD_SPECULAR_SLOPE:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetSpecularSlope(value);
            }
            break;
            case WORD_TRANSLUCENCY:
            {
                float value;
                ParseBlockedFloat(buffer, value);
                mat->SetTranslucency(value);
            }
            break;
            case WORD_TEXTURE_SLOT:
            {
                std::unique_ptr<Attributes::TextureSlot> slot(new Attributes::TextureSlot(mat));
                ParseTextureSlot(buffer, *slot);
                mat->AddTextureSlot(slot.release());
            }
            break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

//    bool ParseMaterials(Core::Buffer& buffer, Scene::SceneGraph*)
//    {
//        CHECK_START(buffer);
//        Core::String name;
//        while (1)
//        {
//            Core::String word = buffer.ReadWord();
//            KeywordCode code = Parse(word);
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
