#ifndef _H_PUNK_VIRTUAL_TERRAIN_OBSERVER
#define _H_PUNK_VIRTUAL_TERRAIN_OBSERVER

#include <config.h>
#include <core/object.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class TerrainManager;
	class TerrainView;

    class PUNK_ENGINE_API TerrainObserver : public Core::IObject
	{
	public:
		virtual ~TerrainObserver();

		TerrainView* GetTerrainView() { return m_view; }
		const TerrainView* GetTerrainView() const { return m_view; }

		void SetPosition(const Math::vec3& value);

	private:
		TerrainObserver(TerrainView* view);

	private:
		//	should be destroyed in destructor
		TerrainView* m_view;
		friend class TerrainManager;
	};

	typedef TerrainObserver* TerrainObserverRef;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_OBSERVER
