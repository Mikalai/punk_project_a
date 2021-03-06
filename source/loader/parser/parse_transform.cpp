#include <attributes/transform/itransform.h>
#include <attributes/animation/module.h>
#include "parser.h"
#include "parse_simple.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

	PUNK_ENGINE_LOCAL bool ParseTransform(Core::Buffer &buffer, void* object) {

		Attributes::ITransform* transform = (Attributes::ITransform*)object;
		Parser* parser = GetDefaultParser();

		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				throw Error::LoaderException(L"Can't parse object");

			Core::String word = buffer.ReadWord();

			KeywordCode code = ParseKeyword(word);
			switch (code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_LOCATION:
			{
				Math::vec3 value;
				parser->Parse<Math::vec3>(WORD_VEC3F, buffer, value);
				transform->SetPosition(value);
			}
				break;
			case WORD_ROTATION:
			{
				Math::quat value;
				parser->Parse<Math::quat>(WORD_QUAT, buffer, value);
				transform->SetRotation(value);
			}
				break;
			case WORD_SCALE:
			{
				Math::vec3 value;
				parser->Parse<Math::vec3>(WORD_VEC3F, buffer, value);
				transform->SetScale(value);
			}
				break;
			case WORD_ENTITY_NAME:
			{
				Core::String value;
				parser->Parse<Core::String>(WORD_STRING, buffer, value);
			}
				break;
			case WORD_BOUNDING_BOX:
			{
			}
				break;
			case WORD_ACTION_REF:
			{
				Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				Attributes::IAnimated* animated = nullptr;
				transform->QueryInterface(Attributes::IID_IAnimated, (void**)&animated);                
				if (animated) {
					animated->AddAnimation(name);
					animated->Release();
				}
			}
				break;
			default:
				throw Error::LoaderException(L"Unexpected keyword " + word);
			}
		}
	}

	PUNK_REGISTER_PARSER(WORD_TRANSFORM, ParseTransform);
}
PUNK_ENGINE_END
