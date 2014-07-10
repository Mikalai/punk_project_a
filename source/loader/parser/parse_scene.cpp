#include <system/factory/module.h>
#include <core/module.h>
#include <scene/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
	PUNK_ENGINE_LOCAL bool ParseSceneGraph(Core::Buffer& buffer, void* object)
    {
		SceneModule::IScene* value = (SceneModule::IScene*)object;
		Parser* parser = GetDefaultParser();

        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(ParseKeyword(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_NODE:
            {
                auto node = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
                parser->Parse(WORD_NODE, buffer, node.get());
                value->GetRoot()->AddChild(node);
                //value->SetRoot(node.release());
            }
            break;            
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }

	PUNK_REGISTER_PARSER(WORD_SCENE_GRAPH, ParseSceneGraph);
}
PUNK_ENGINE_END
