#include <core/module.h>
#include <scene/module.h>
#include "parse_scene_node.h"
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
	PUNK_ENGINE_LOCAL bool ParseSceneGraph(Core::Buffer& buffer, Scene::ISceneGraph* value)
    {
        while (!buffer.IsEnd())
        {
            Core::String word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
            return true;
            case WORD_NODE:
            {
                Scene::INode* node = Scene::CreateRootNode(value);
                ParseSceneNode(buffer, node);
                //value->SetRoot(node.release());
            }
            break;            
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
PUNK_ENGINE_END
