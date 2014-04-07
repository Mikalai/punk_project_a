#ifndef PARSE_SCENE_H
#define PARSE_SCENE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Scene { class ISceneGraph; }
namespace Loader {
    PUNK_ENGINE_LOCAL bool ParseSceneGraph(Core::Buffer& buffer, Scene::ISceneGraph* value);
}
PUNK_ENGINE_END

#endif // PARSE_SCENE_H
