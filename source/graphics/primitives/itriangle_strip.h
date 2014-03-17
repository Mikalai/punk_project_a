#ifndef ITRIANGLE_STRIP_H
#define ITRIANGLE_STRIP_H

#include <cstdint>
#include <config.h>
#include "irenderable.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVertexArray;
    class IVideoDriver;

    class PUNK_ENGINE_API ITriangleStrip : public IRenderable {
    public:
        virtual void Cook(const IVertexArray* value) = 0;
    };

    namespace Constructor {
        extern "C" PUNK_ENGINE_API ITriangleStrip* CreateTriangleStrip(std::int64_t vertex_type, class IVideoDriver* driver);
    }
}
PUNK_ENGINE_END

#endif // ITRIANGLE_STRIP_H
