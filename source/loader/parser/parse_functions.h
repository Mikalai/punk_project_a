#ifndef PARSE_FUNCTIONS_H
#define PARSE_FUNCTIONS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
    class Scene;
}
namespace Core {
    class Buffer;
}
namespace IoModule {
    extern bool ParseWorld(Core::Buffer& buffer, SceneModule::Scene* scene);                           
}
PUNK_ENGINE_END

#endif // PARSE_FUNCTIONS_H
