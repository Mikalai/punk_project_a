#include "io_river.h"

void SaveRiver(Core::Buffer *buffer, const Core::Object *o)
{
    System::SaveObject(buffer, o);
    const River* r = Cast<const River*>(o);
    System::SaveString(buffer, r->m_filename);
    System::SaveString(buffer, r->m_name);
    Math::SaveVector3f(buffer, r->m_position);
    Math::SaveVector3f(buffer, r->m_flow_direction);
    buffer->WriteReal32(r->m_flow_speed);
    System::Factory::Save(buffer, r->m_geom);
}

void LoadRiver(Core::Buffer *buffer, Core::Object *o)
{
    System::LoadObject(buffer, o);
    River* r = Cast<River*>(o);
    System::LoadString(buffer, r->m_filename);
    System::LoadString(buffer, r->m_name);
    Math::LoadVector3f(buffer, r->m_position);
    Math::LoadVector3f(buffer, r->m_flow_direction);
    r->m_flow_speed = buffer->ReadReal32();
    r->m_geom = Cast<StaticGeometry*>(System::Factory::Load(buffer));
}
