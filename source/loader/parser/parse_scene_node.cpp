#include <memory>
#include <attributes/module.h>
#include <scene/module.h>
#include "parser.h"
#include "parse_simple.h"
#include "parse_scene_node.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseSceneNode(Core::Buffer &buffer, Scene::INode *node)
    {
        CHECK_START(buffer);
        while (1)
        {
            if (buffer.IsEnd())
                throw Error::LoaderException(L"Can't parse object");

            Core::String word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_NODE:
            {
                Scene::INodeUniquePtr child = Scene::CreateNode(node);
                ParseSceneNode(buffer, child.get());
                node->AddChild(child.release());
            }
                break;
            case WORD_NAME:
            {
                Core::String name;
                ParseBlockedString(buffer, name);
                node->SetAttribute(new Scene::Attribute<Core::String>("Name", name));
            }
                break;
            case WORD_ENTITY_NAME:
            {
                Core::String value;
                ParseBlockedString(buffer, value);
                node->SetAttribute(new Scene::Attribute<Core::String>("Type", "FileProxy"));
                node->SetAttribute(new Scene::Attribute<Core::String>("Filename", value));
            }
                break;
            default:
                throw Error::LoaderException(L"Unexpected keyword " + word);
            }
        }
    }
}
PUNK_ENGINE_END
