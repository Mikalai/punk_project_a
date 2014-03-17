#include <graphics/error/module.h>
#include "irender_context.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	IRenderContext::IRenderContext()
		: m_was_modified(false)
        , m_vertex_attributes(VertexComponent::NoComponent::Value())
	{}

	IRenderContext::~IRenderContext()
	{
	}
}
PUNK_ENGINE_END
