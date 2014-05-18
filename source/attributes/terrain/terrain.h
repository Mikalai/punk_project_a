#ifndef _H_PUNK_VIRTUAL_TERRAIN
#define _H_PUNK_VIRTUAL_TERRAIN

#include <config.h>
#include <core/object.h>
#include <math/vec2.h>
#include <math/matrix.h>
#include <math/smart_matrix.h>
#include <attributes/material/imaterial.h>
#include "terrain_cell.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Terrain : public Core::IObject
	{
	public:
		Terrain();
		virtual ~Terrain();

		void SetNumBlocks(int value);
		int GetNumBlocks() const { return m_core.m_num_blocks; }

		void SetBlockScale(float value) { m_core.m_block_scale = value; }
		float GetBlockScale() const { return m_core.m_block_scale; }

		void SetBlocksSize(int value) { m_core.m_block_size = value; }
		int GetBlockSize() const { return m_core.m_block_size; }
		
		void SetHeightScale(float value) { m_core.m_height_scale = value; }
		float GetHeightScale() const { return m_core.m_height_scale; }

		void SetOrigin(const Math::vec2& value) { m_core.m_origin = value; }
		const Math::vec2& GetOrigin() const { return m_core.m_origin; }

//		virtual void Save(Core::Buffer* buffer) const;
//		virtual void Load(Core::Buffer* buffer);

		const Core::String ToString() const;

		bool AddOrUpdateCell(const TerrainCell& value);

		TerrainCell* GetCell(int x, int y) { return m_cells.At(y, x); }
		const TerrainCell* GetCell(int x, int y) const { return m_cells.At(y, x); }

		IMaterial* GetMaterial() { return m_material; }
		void SetMaterial(IMaterial* value) { m_material = value; }

	private:

        struct CoreData
		{
			char m_head[16];
			int m_num_blocks;
			float m_block_scale;
			int m_block_size;
			float m_height_scale;
			Math::vec2 m_origin;		

            CoreData();
		};

        CoreData m_core;

		//	should be destroyed
		Math::Matrix<TerrainCell*> m_cells;
		IMaterial* m_material;
	};

	typedef Terrain* TerrainRef;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TERRAIN
