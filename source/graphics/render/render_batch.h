#ifndef _H_PUNK_RENDER_BATCH
#define _H_PUNK_RENDER_BATCH

#include <list>
#include <core/poolable.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class CoreState;
    class IRenderable;

    class Batch : public Core::Poolable<Batch>
    {
    public:
        ~Batch();
        CoreState* m_state;
		Core::Pointer<IRenderable> m_renderable{ nullptr, Core::DestroyObject };
    };
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_RENDER_BATCH
