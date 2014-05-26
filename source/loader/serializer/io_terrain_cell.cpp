#include <attributes/terrain/terrain_cell.h>
#include "io_string.h"
#include "io_vector.h"
#include "io_terrain_cell.h"

PUNK_ENGINE_BEGIN
namespace IoModule {
    void SaveTerrainCell(Core::Buffer *buffer, const Attributes::TerrainCell* cell)
    {
        SaveVector2i(buffer, cell->GetLocation());
        buffer->WriteReal32(cell->GetBaseHeight());
        buffer->WriteSigned32(cell->IsValid());
        SaveString(buffer, cell->GetName());
        //m_source.Save(buffer);
    }

    void LoadTerrainCell(Core::Buffer *buffer, Attributes::TerrainCell* cell)
    {
        Math::ivec2 location;
        LoadVector2i(buffer, location);
        cell->SetLocation(location);

        cell->SetBaseHeight(buffer->ReadReal32());
        bool valid = buffer->ReadSigned32();
        if (valid)
            cell->Validate();
        else
            cell->Invalidate();
        Core::String name;
        LoadString(buffer, name);
        cell->SetName(name);
        //m_source.Load(buffer);
    }
}
PUNK_ENGINE_END
