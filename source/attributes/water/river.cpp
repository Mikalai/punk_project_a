#include <string/module.h>
#include "river.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti River::Type{"Attributes.River",
                           typeid(River).hash_code(), {&Core::Object::Type}};

    River::River()
        : m_geom(nullptr)
        , m_task(nullptr)
    {}

    River::~River()
    {}

    void River::SetGeometry(StaticGeometry* value)
    {
        m_geom = value;
    }

    const StaticGeometry* River::GetGeometry() const
    {
        return m_geom;
    }

    StaticGeometry* River::GetGeometry()
    {
        return m_geom;
    }

    void River::SetFlowSpeed(float value)
    {
        m_flow_speed = value;
    }

    float River::GetFlowSpeed() const
    {
        return m_flow_speed;
    }

    void River::SetFlowDirection(const Math::vec3& value)
    {
        m_flow_direction = value;
    }

    const Math::vec3& River::GetFlowDirection() const
    {
        return m_flow_direction;
    }

    void River::SetStaticMeshFilename(const Core::String& value)
    {
        m_filename = value;
    }

    const Core::String River::GetStaticMeshFilename() const
    {
        return m_filename;
    }

    void River::SetStreamPosition(const Math::vec3& value)
    {
        m_position = value;
    }

    const Math::vec3& River::GetStreamPosition() const
    {
        return m_position;
    }

    Utility::AsyncParserTask* River::Task() const
    {
        return m_task;
    }

    Utility::AsyncParserTask* River::Task(Utility::AsyncParserTask* value)
    {
        if (m_task)
            delete m_task;
        return m_task = value;
    }

    void River::SetName(const Core::String& name)
    {
        m_name = name;
    }

    const Core::String& River::GetName() const
    {
        return m_name;
    }    
}
PUNK_ENGINE_END
