#include <memory>
#include <system/factory/module.h>
#include <attributes/module.h>
#include <scene/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule {
    
	PUNK_ENGINE_LOCAL bool ParseSceneNode(Core::Buffer& buffer, void* object)
    {
		Core::Pointer<SceneModule::INode> node{ (SceneModule::INode*)object, Core::DestroyObject };
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
                auto child = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
                ParseSceneNode(buffer, child.get());
				node->AddChild(child);
            }
                break;
            case WORD_NAME:
            {
                Core::String name;
				parser->Parse<Core::String>(WORD_STRING, buffer, name);
				{
                    auto text = System::CreateInstancePtr<Attributes::IText>(Attributes::CLSID_Text, Attributes::IID_IText);
                    if (text) {
						text->SetText(name);
                        node->Add<Attributes::IText>(L"Name", text);
					}
				}
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
				parser->Parse<Core::String>(WORD_STRING, buffer, value);
				{
					auto stub = System::CreateInstancePtr<Attributes::IFileStub>(Attributes::CLSID_FileStub, Attributes::IID_IFileStub);
					if (stub) {
						stub->SetFilename(value);
                        node->Add<Attributes::IFileStub>("Filename", stub);
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
