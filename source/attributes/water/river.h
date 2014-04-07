#ifndef PUNK_VIRTUAL_RIVER_H
#define PUNK_VIRTUAL_RIVER_H

#include <attributes/data/static_geometry.h>

PUNK_ENGINE_BEGIN

namespace Utility {
    class AsyncParserTask;
}

namespace Attributes
{
    class River : public Core::Object
    {
    public:
        River();
        River(const River&) = delete;
        River& operator = (const River&) = delete;
        virtual ~River();

        void SetGeometry(StaticGeometry* value);
        const StaticGeometry* GetGeometry() const;
        StaticGeometry* GetGeometry();

        void SetFlowSpeed(float value);
        float GetFlowSpeed() const;

        void SetFlowDirection(const Math::vec3& value);
        const Math::vec3& GetFlowDirection() const;

        void SetStaticMeshFilename(const Core::String& value);
        const Core::String GetStaticMeshFilename() const;

        void SetStreamPosition(const Math::vec3& value);
        const Math::vec3& GetStreamPosition() const;

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

        void SetName(const Core::String& name);
        const Core::String& GetName() const;

    private:
        Math::vec3 m_position;
        Core::String m_filename;
        float m_flow_speed;
        Math::vec3 m_flow_direction;
        StaticGeometry* m_geom;
        Utility::AsyncParserTask* m_task;
        Core::String m_name;
        PUNK_OBJECT(River)
    };
}
PUNK_ENGINE_END

#endif // PUNK_VIRTUAL_RIVER_H
