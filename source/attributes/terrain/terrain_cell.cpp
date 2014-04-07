#include <core/module.h>
#include <system/errors/module.h>
#include <system/logger/module.h>
#include "terrain_cell.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    void TerrainRawDataSource::Save(Core::Buffer *buffer) const
	{
        buffer->WriteString(m_raw_file);
	}

    void TerrainRawDataSource::Load(Core::Buffer *buffer)
	{
        m_raw_file = buffer->ReadString();
	}

    TerrainCell::CoreData::CoreData()
		: m_location(0,0)
		, m_base_height(0)
		, m_is_valid(false)
	{}
	
	TerrainCell::TerrainCell()
		: m_name(L"cell_0_0")	
		, m_loading(false)
		, m_data_cache(nullptr)
	{}

	TerrainCell::~TerrainCell()
	{
		delete m_data_cache;
		m_data_cache = nullptr;
	}

}
PUNK_ENGINE_END
