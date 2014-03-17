#include <graphics/state/module.h>
#include <graphics/primitives/module.h>
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	Batch::~Batch()	{
		delete m_state;
		m_state = nullptr;
        if (m_destroy) {
            DestroyRenderable(m_renderable);
			m_renderable = nullptr;
		}
	}
}
PUNK_ENGINE_END
