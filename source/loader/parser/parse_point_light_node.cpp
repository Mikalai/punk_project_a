//#include "../../virtual/data/lights/point_light.h"
//#include "parse_functions.h"

//namespace IoModule
//{
//    bool ParsePointLightNode(Core::Buffer& buffer, SceneModule::PointLightNode* value)
//    {
//        CHECK_START(buffer);
//        std::unique_ptr<Attributes::PointLight> light(new Attributes::PointLight);
//        while (!buffer.IsEnd())
//        {
//            Core::String word = buffer.ReadWord();
//            switch(ParseKeyword(word))
//            {
//            case WORD_CLOSE_BRACKET:
//                value->SetPointLight(light.release());
//                return true;
//            case WORD_NAME:
//            {
//                Core::String name;
//                ParseBlockedString(buffer, name);
//                value->SetName(name);
//                value->SetStorageName(name);
//            }
//                break;
//            case WORD_COLOR:
//            {
//                Math::vec3 color;
//                ParseBlockedVector3f(buffer, color);
//                light->SetColor(color);
//            }
//                break;
//            case WORD_DISTANCE:
//            {
//                float dst;
//                ParseBlockedFloat(buffer, dst);
//                light->SetDistance(dst);
//            }
//                break;
//            case WORD_ENERGY:
//            {
//                float energy;
//                ParseBlockedFloat(buffer, energy);
//                light->SetEnergy(energy);
//            }
//                break;
//            case WORD_LINEAR_ATTENUATION:
//            {
//                float v;
//                ParseBlockedFloat(buffer, v);
//                light->SetLinearAttenuation(v);
//            }
//                break;
//            case WORD_QUADRATIC_ATTENUATION:
//            {
//                float v;
//                ParseBlockedFloat(buffer, v);
//                light->SetQuadraticAttenuation(v);
//            }
//                break;
//            default:
//                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
//            }
//        }
//        return true;
//    }
//}
