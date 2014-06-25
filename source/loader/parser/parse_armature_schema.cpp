#include <attributes/skinning/module.h>
#include <system/factory/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{

	/// ParseKeyword single armature
	bool ParseArmatureSchema(Core::Buffer& buffer, void* object)
	{
		Attributes::IArmatureSchema *value = (Attributes::IArmatureSchema*)object;
		Parser* parser = GetDefaultParser();

		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
			{
				throw Error::LoaderException("Can't parse object");
				return false;
			}

			Core::String word = buffer.ReadWord();
			KeywordCode index;
			switch (index = ParseKeyword(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ACTION_REF:
			{
				Core::String action;
				parser->Parse<Core::String>(WORD_STRING, buffer, action);
				value->AddSupportedAction(action);
			}
				break;
			case WORD_BONE:
			{
                auto bone = System::CreateInstancePtr<Attributes::IBone>(Attributes::IID_IBone);
				parser->Parse(WORD_BONE, buffer, bone.get());
				value->AddBone(bone.get());
			}
				break;
			default:
				throw Error::LoaderException(L"Unknown keyword: " + word);
			}
		}
		return false;
	}

	PUNK_REGISTER_PARSER(WORD_ARMATURE_SCHEMA, ParseArmatureSchema);

	//bool ParseArmatures(Core::Buffer& buffer)
	//{
	//	CHECK_START(buffer);
	//	while (1)
	//	{
	//		Core::String word = buffer.ReadWord();
	//		KeywordCode code = ParseKeyword(word);
	//		switch (code)
	//		{
	//		case WORD_CLOSE_BRACKET:
	//			return true;
	//		case WORD_ARMATURE:
	//		{
	//			std::unique_ptr<Attributes::Armature> armature(new Attributes::Armature);
	//			ParseArmature(buffer, armature.get());
	//			armature.release();
	//		}
	//			break;
	//		default:
	//			throw Error::LoaderException(L"Unexpected keyword " + word);
	//		}
	//	}
	//	return false;
	//}
}
PUNK_ENGINE_END
