#ifndef PARSE_FUNCTIONS_H
#define PARSE_FUNCTIONS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Scene {
    class SceneGraph;
}
namespace Core {
    class Buffer;
}
namespace Loader {
    extern bool ParseWorld(Core::Buffer& buffer, Scene::SceneGraph* scene);                           
}
PUNK_ENGINE_END

#endif // PARSE_FUNCTIONS_H
