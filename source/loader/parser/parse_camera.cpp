#include <attributes/camera/module.h>
#include "parser.h"
#include "parse_rotation_track.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	bool ParsePerspectiveCamera(Core::Buffer& buffer, void* object)
	{
		Attributes::IPerspectiveCamera* camera = (Attributes::IPerspectiveCamera*)object;
		Parser* parser = GetDefaultParser();

		CHECK_START(buffer);

		Core::String name;

		while (1)
		{
			if (buffer.IsEnd())
			{
				throw Error::LoaderException(L"Can't parse object");
			}

			const Core::String word = buffer.ReadWord();
			KeywordCode index = ParseKeyword(word);
			switch (index)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
			{
				Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				camera->SetName(name);
			}
				break;
			case WORD_FOV:
			{
				float v;
				parser->Parse<float>(WORD_FLOAT, buffer, v);
				camera->SetFieldOfView(v);
			}
				break;
			case WORD_NEAR_PLANE:
			{
				float v;
				parser->Parse<float>(WORD_FLOAT, buffer, v);
				camera->SetNearClipPlane(v);
			}
				break;
			case WORD_FAR_PLANE:
			{
				float v;
				parser->Parse<float>(WORD_FLOAT, buffer, v);
				camera->SetFarClipPlane(v);
			}
				break;
			case WORD_FOCUS:
			{
				float v;
				parser->Parse<float>(WORD_FLOAT, buffer, v);
				//	TODO: ignore
			}
				break;
			case WORD_UP_VECTOR:
			{
				Math::vec3 up_vector;
				parser->Parse<Math::vec3>(WORD_VEC3F, buffer, up_vector);
				camera->SetUpVector(up_vector);
			}
				break;
			default:
				throw Error::LoaderException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	PUNK_REGISTER_PARSER(WORD_PERSPECTIVE_CAMERA, ParsePerspectiveCamera);
}
PUNK_ENGINE_END
