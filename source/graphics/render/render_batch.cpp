#include <graphics/state/module.h>
#include <graphics/primitives/module.h>
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	Batch::~Batch()	{
		delete m_state;
		m_state = nullptr;
	}
}
PUNK_ENGINE_END
