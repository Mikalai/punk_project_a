#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
    class ITimer
    {
    public:
        virtual double GetTime() const = 0;
        virtual double GetElapsedSeconds() const = 0;
        virtual double GetElapsedMiliseconds() const = 0;
        virtual double Reset() = 0;
    };

    PUNK_ENGINE_API ITimer* CreateTimer();
    PUNK_ENGINE_API void DestroyTimer(ITimer* value);
}
PUNK_ENGINE_END

#endif // TIMER_INTERFACE_H
