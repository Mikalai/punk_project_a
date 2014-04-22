#ifndef IPOINTS_H
#define IPOINTS_H

#include <memory>
#include <cstdint>
#include <config.h>
#include "irenderable.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVertexArray;
    class IVideoDriver;

    class PUNK_ENGINE_API IPoints : public IRenderable {
    public:
        virtual void Cook(const IVertexArray* value) = 0;
    };

    using IPointsUniquePtr = std::unique_ptr<IPoints, void (*)(IRenderable*)>;

    extern PUNK_ENGINE_API IPointsUniquePtr CreatePoints(std::int64_t vertex_type, class IVideoDriver* driver);
}
PUNK_ENGINE_END


#endif // IPOINTS_H
