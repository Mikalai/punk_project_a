#ifndef PUNK_VIRTUAL_SUN_H
#define PUNK_VIRTUAL_SUN_H

#include <config.h>
#include <core/object.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Sun : public Core::IObject
    {
    public:
        Sun();
        Sun(const Sun&) = delete;
        Sun& operator = (const Sun&) = delete;
        virtual ~Sun();

        void SetEnergy(float value);
        float GetEnergy() const;
        void SetColor(const Math::vec3& value);
        const Math::vec3& GetColor() const;

        void SetName(const Core::String& value);
        const Core::String& GetName() const;

    private:
        float m_energy;
        Math::vec3 m_color;
        Core::String m_name;

        PUNK_OBJECT_DEFAULT_IMPL(Sun)
    };

}
PUNK_ENGINE_END

#endif // PUNK_VIRTUAL_SUN_H
