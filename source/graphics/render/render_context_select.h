#ifndef H_PUNK_GPU_RENDER_SELECT
#define H_PUNK_GPU_RENDER_SELECT

#include <config.h>
#include "irender_context.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    class IRenderContext;
    class CoreState;

    PUNK_ENGINE_LOCAL RenderContextType SelectRenderContext(CoreState* state);
}
PUNK_ENGINE_END

#endif // H_PUNK_GPU_RENDER_SELECT
