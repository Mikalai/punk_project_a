#include <memory>
#include <core/ifactory.h>
#include <attributes/module.h>
#include <scene/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule {
    
	PUNK_ENGINE_LOCAL bool ParseSceneNode(Core::Buffer& buffer, void* object)
    {
		SceneModule::INode* node = (SceneModule::INode*)object;
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
				SceneModule::INode* child = nullptr;
				Core::GetFactory()->CreateInstance(SceneModule::IID_INode, (void**)&child);
                ParseSceneNode(buffer, child);
                node->AddChild(child);
            }
                break;
            case WORD_NAME:
            {
                Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				{
					Attributes::IText* text = nullptr;
					Core::GetFactory()->CreateInstance(Attributes::IID_IText, (void**)&text);
					if (text) {
						text->SetText(name);
						node->Set<Attributes::IText>("Name", text);
					}
				}
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
				parser->Parse<Core::String>(WORD_STRING, buffer, value);
				{
					Attributes::IFileStub* stub = nullptr;
					Core::GetFactory()->CreateInstance(Attributes::IID_IFileStub, (void**)&stub);
					if (stub) {
						stub->SetFilename(value);
						node->Set<Attributes::IFileStub>("Filename", stub);
					}
				}                
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
