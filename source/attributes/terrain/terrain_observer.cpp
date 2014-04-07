#include "terrain_observer.h"
#include "terrain_view.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	TerrainObserver::TerrainObserver(TerrainView* view)
		: m_view(view)
	{
	}

	void TerrainObserver::SetPosition(const Math::vec3& value)
	{
		m_view->UpdatePosition(value.XZ());
	}

	TerrainObserver::~TerrainObserver()
	{
		safe_delete(m_view);
	}
}
PUNK_ENGINE_END
