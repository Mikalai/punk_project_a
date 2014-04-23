#ifndef PARSE_MATERIAL_H
#define PARSE_MATERIAL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class Material; }
namespace Loader {
    extern bool ParseMaterial(Core::Buffer& buffer, Attributes::Material* mat);
    //extern bool ParseMaterials(Core::Buffer& buffer, Scene::SceneGraph* scene);
}
PUNK_ENGINE_END

#endif // PARSE_MATERIAL_H