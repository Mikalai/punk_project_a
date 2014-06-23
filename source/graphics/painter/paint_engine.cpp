#include "paint_engine.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    PaintEngine::PaintEngine()
		: m_device(nullptr)
		, m_painter(nullptr)
	{}

	PaintEngine::~PaintEngine()
	{}
}
PUNK_ENGINE_END
