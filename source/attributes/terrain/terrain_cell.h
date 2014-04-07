#ifndef _H_PUNK_VIRTUAL_TERRAIN_CELL
#define _H_PUNK_VIRTUAL_TERRAIN_CELL

#include <config.h>
#include <string/string.h>
#include <math/vec2.h>
#include "terrain_data.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_API TerrainRawDataSource
	{
	public:
		void SetRawFile(const Core::String& filename) { m_raw_file = filename; }
		const Core::String& GetRawFile() const { return m_raw_file; }

		void Save(Core::Buffer* buffer) const;
		void Load(Core::Buffer* buffer);

	private:
		Core::String m_raw_file;
	};

	class PUNK_ENGINE_API TerrainCell
	{
	public:
		TerrainCell();
		virtual ~TerrainCell();

		void SetLocation(const Math::ivec2& value) { m_core.m_location = value; }
		const Math::ivec2& GetLocation() const { return m_core.m_location; }

		void SetBaseHeight(float value) { m_core.m_base_height = value; }
		float GetBaseHeight() const { return m_core.m_base_height; }

        bool IsValid() const { return m_core.m_is_valid; }

		void Validate() { m_core.m_is_valid = true; }
		void Invalidate() { m_core.m_is_valid = false; }

		void SetName(const Core::String& value) { m_name = value; }
		const Core::String& GetName() const { return m_name; }

		void SetRawDataSource(const TerrainRawDataSource& value) { m_source = value; }
		const TerrainRawDataSource& GetRawDataSource() const { return m_source; }

		void Save(Core::Buffer* buffer) const;
		void Load(Core::Buffer* buffer);

		/**
		*	This method is used by the main thread, when data is needed.
		*	It tries to get cached data. If no cached data in cell main thread
		*	initiates data loading process. 
		*/
		TerrainData* GetDataCached() { return m_data_cache; }
		
		/**
		*	This is used to place new data to the cell
		*/
		void SetDataCached(TerrainData* value) 
		{ 
			m_data_cache = value; 
			m_loading = false;
		}

		/**
		*	Intentionally drop cache
		*/
		void DropCache() 
		{ 
			delete m_data_cache;
			m_data_cache = nullptr;
			//	mark cell as cell without data
			//	m_loaded = false;
		}

		/**
		*	Marks cell as being loaded now
		*/
		void InitiateLoading()
		{
			m_loading = true;
		}

		/**
		*	Returns true if request for loading data for current cell was created
		*/
		bool IsLoading() const
		{
			return m_loading;
		}

	private:		

        struct CoreData
		{
			Math::ivec2 m_location;
			float m_base_height;
			bool m_is_valid;

            CoreData();
		};

        CoreData m_core;
		Core::String m_name;
		TerrainRawDataSource m_source;
		
		// This field is used expliciply for caching purposes
		//	it is not saved or loaded ever.
		// should be deleted in destructor
		TerrainData* m_data_cache;
		// Used to indicate state of the cell. if true it means that
		//	request was created for loading this part of terriotory
		bool m_loading;
		// Indicates that cell contains data 
		// bool m_loaded;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TERRAIN_CELL
