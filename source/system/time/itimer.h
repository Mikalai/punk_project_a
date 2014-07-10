#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
	DECLARE_PUNK_GUID(IID_ITimer, "F57B801C-AA35-4631-A7E5-53E10B41C404");
	DECLARE_PUNK_GUID(CLSID_Timer, "FCCFF0DF-0E1E-4016-BB1E-EC9EDE4D4BB6");

    class ITimer : public Core::IObject
    {
    public:
        virtual double GetTime() const = 0;
        virtual double GetElapsedSeconds() const = 0;
        virtual double GetElapsedMiliseconds() const = 0;
        virtual void Reset() = 0;
    };
}
PUNK_ENGINE_END

#endif // TIMER_INTERFACE_H
