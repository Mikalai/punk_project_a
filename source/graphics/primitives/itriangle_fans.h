#ifndef ITRIANGLE_FANS_H
#define ITRIANGLE_FANS_H

#include <cstdint>
#include <config.h>
#include "irenderable.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVertexArray;
    class IVideoDriver;

    class PUNK_ENGINE_API ITriangleFan : public IRenderable {
    public:
        virtual void Cook(const IVertexArray* value) = 0;
    };

    namespace Constructor {
        extern "C" PUNK_ENGINE_API ITriangleFan* CreateTriangleFan(std::int64_t vertex_type, class IVideoDriver* driver);
    }
}
PUNK_ENGINE_END

#endif // ITRIANGLE_FANS_H
