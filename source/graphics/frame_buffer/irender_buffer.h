#ifndef IRENDER_BUFFER_H
#define IRENDER_BUFFER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class IRenderBuffer {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}
PUNK_ENGINE_END

#endif // IRENDER_BUFFER_H
