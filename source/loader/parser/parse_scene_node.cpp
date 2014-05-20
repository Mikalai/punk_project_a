#include <memory>
#include <core/factory.h>
#include <attributes/module.h>
#include <scene/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    
	PUNK_ENGINE_LOCAL bool ParseSceneNode(Core::Buffer& buffer, void* object)
    {
		Scene::INode* node = (Scene::INode*)object;
		Parser* parser = GetDefaultParser();

        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = ParseKeyword(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NODE:
            {
				Scene::INode* child = nullptr;
				Core::GetFactory()->CreateInstance(Scene::IID_INode, (void**)&child);
                ParseSceneNode(buffer, child);
                //node->AddChild(child.release());
            }
                break;
            case WORD_NAME:
            {
                Core::String name;
                parser->Parse<Core::String>(WORD_STRING, buffer, name);
                node->SetAttribute(new Scene::Attribute<Core::String>("Name", name));
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
                parser->Parse<Core::String>(WORD_STRING, buffer, value);
                node->SetAttribute(new Scene::Attribute<Core::String>("Type", "FileProxy"));
                node->SetAttribute(new Scene::Attribute<Core::String>("Filename", value));
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }

	PUNK_REGISTER_PARSER(WORD_NODE, ParseSceneNode);
}
PUNK_ENGINE_END
