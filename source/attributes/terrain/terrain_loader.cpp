#include <string/module.h>
#include <system/logger/module.h>
#include <system/filesystem/module.h>
#include <system/environment.h>
#include "terrain_loader.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	TerrainLoader::TerrainLoader(const Core::String& map_name, const Math::ivec2& block)
		: m_map_name(map_name)
		, m_block(block)
		, m_data(nullptr)
	{}

	System::StreamingStepResult TerrainLoader::Load()
	{
        Core::String filename = System::Environment::Instance()->GetMapFolder() + m_map_name + Core::String("/{0}_{1}.raw")
                .arg(m_block.X()).arg(m_block.Y());
		
		Core::Buffer buffer;
        if (!System::BinaryFile::Load(filename, buffer)) {
            System::GetDefaultLogger()->Error(L"Can't load " + filename);
            return System::StreamingStepResult::STREAM_ERROR;
        }
		m_size = buffer.GetSize();
		m_data = buffer.Release();
		return System::StreamingStepResult::STREAM_OK;
	}

	System::StreamingStepResult TerrainLoader::Decompress(void** data, unsigned* size)
	{
		*data = m_data;
		*size = m_size;
		return System::StreamingStepResult::STREAM_OK;
	}

	System::StreamingStepResult TerrainLoader::Destroy()
	{
		return System::StreamingStepResult::STREAM_OK;
	}

	TerrainLoader::~TerrainLoader()
	{
		//	it's ok, i hope. better call destroy separately
		Destroy();
	}
}
PUNK_ENGINE_END
