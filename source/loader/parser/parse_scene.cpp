#include <core/module.h>
#include <scene/module.h>
#include "parse_scene_node.h"
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseSceneGraph(Core::Buffer& buffer, Scene::ISceneGraph* value)
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
                Scene::INodeUniquePtr node = Scene::CreateNode(nullptr);
                ParseSceneNode(buffer, node.get());
                value->SetRoot(node.release());
            }
            break;            
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }
}
PUNK_ENGINE_END
