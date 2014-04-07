#ifndef PARSE_ARMATURE_H
#define PARSE_ARMATURE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class Armature; }
namespace Loader {
    extern bool ParseArmature(Core::Buffer& buffer, Attributes::Armature* armature);
    extern bool ParseArmatures(Core::Buffer& buffer);
}
PUNK_ENGINE_END


#endif // PARSE_ARMATURE_H
