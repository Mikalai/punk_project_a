#include <core/ifactory.h>
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
				SceneModule::INode* node{ nullptr };
				Core::GetFactory()->CreateInstance(SceneModule::IID_INode, (void**)&node);
                parser->Parse(WORD_NODE, buffer, node);
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
