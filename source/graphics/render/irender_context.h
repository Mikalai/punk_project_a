#ifndef _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
#define _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT

#include <config.h>
#include "render_context_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class IVideoDriver;
	class IShader;
	class CoreState;

    class IRenderContext {
	public:        		
        virtual void Begin() = 0;
		virtual void ApplyState(const CoreState& state) = 0;
        virtual void End() = 0;
		virtual RenderContextType GetType() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
