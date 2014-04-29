#include <attributes/data/transform.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_static_mesh.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    bool ParseSceneTransform(Core::Buffer &buffer, Attributes::Transform *transform) {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;            
            case WORD_LOCATION:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                transform->SetPosition(value);
            }
                break;
            case WORD_ROTATION:
            {
                Math::quat value;
                ParseBlockedQuaternionf(buffer, value);
                transform->SetRotation(value);
            }
                break;
            case WORD_SCALE:
            {
                Math::vec3 value;
                ParseBlockedVector3f(buffer, value);
                transform->SetScale(value);
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
            }
                break;
            case WORD_BOUNDING_BOX:
            {
                Math::BoundingBox bbox;
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }
}
PUNK_ENGINE_END
