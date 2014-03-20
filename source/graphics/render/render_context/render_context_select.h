#ifndef H_PUNK_GPU_RENDER_SELECT
#define H_PUNK_GPU_RENDER_SELECT

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class IRenderContext;
    class CoreState;

    IRenderContext* SelectRenderContext(CoreState* state);
}
PUNK_ENGINE_END

#endif // H_PUNK_GPU_RENDER_SELECT
