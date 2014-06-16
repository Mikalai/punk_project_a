#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
	static const Core::Guid IID_ITimer{ "F57B801C-AA35-4631-A7E5-53E10B41C404" };

    class ITimer : public Core::IObject
    {
    public:
        virtual double GetTime() const = 0;
        virtual double GetElapsedSeconds() const = 0;
        virtual double GetElapsedMiliseconds() const = 0;
        virtual double Reset() = 0;
    };

	using ITimerUniquePtr = Core::UniquePtr < ITimer > ;
}
PUNK_ENGINE_END

#endif // TIMER_INTERFACE_H
