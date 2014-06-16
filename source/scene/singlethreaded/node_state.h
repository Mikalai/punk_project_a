#ifndef NODE_STATE_H
#define NODE_STATE_H

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
    enum class NodeState : std::uint32_t {
        Active,
        Inactive,
        PendingDelete
    };
}
PUNK_ENGINE_END

#endif // NODE_STATE_H
