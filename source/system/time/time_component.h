#ifndef TIME_COMPONENT_H
#define TIME_COMPONENT_H

#include "core/component/module.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class Timer;
    class Clock;

    class PUNK_ENGINE_LOCAL TimeComponent : public Core::Component
    {
    public:
        TimeComponent();

    protected:
        Core::Object* OnCreate(const Core::String &name, const Core::String &type, Core::Object **params) override;

        Timer* m_timer {nullptr};
        Clock* m_clock {nullptr};
    };
}
PUNK_ENGINE_END

#endif // TIME_COMPONENT_H
