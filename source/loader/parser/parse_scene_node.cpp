#include <memory>
#include <system/factory/module.h>
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
                auto child = System::CreateInstancePtr<SceneModule::INode>(SceneModule::IID_INode);
                ParseSceneNode(buffer, child.get());
                node->AddChild(child.get());
            }
                break;
            case WORD_NAME:
            {
                Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				{
                    auto text = System::CreateInstancePtr<Attributes::IText>(Attributes::IID_IText);
                    if (text.get()) {
						text->SetText(name);
                        node->Set<Attributes::IText>("Name", text.get());
					}
				}
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
				parser->Parse<Core::String>(WORD_STRING, buffer, value);
				{
                    auto stub = System::CreateInstancePtr<Attributes::IFileStub>(Attributes::IID_IFileStub);
					if (stub) {
						stub->SetFilename(value);
                        node->Set<Attributes::IFileStub>("Filename", stub.get());
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
