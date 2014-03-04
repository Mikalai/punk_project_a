#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include "config.h"
#include "core/action.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{    
    class ILogConsumer;

    class ILogger
    {
    public:
        virtual void Message(const Core::String& value) = 0;
        virtual void Warning(const Core::String& value) = 0;
        virtual void Error(const Core::String& value) = 0;
        virtual void Info(const Core::String& value) = 0;
        virtual void Write(const Core::String& value) = 0;
        virtual void Debug(const Core::String& value) = 0;
        virtual void AddConsumer(ILogConsumer* consumer) = 0;
        virtual void RemoveConsumer(ILogConsumer* consumer) = 0;
    };

    extern "C" PUNK_ENGINE_API ILogger* GetDefaultLogger();
    extern "C" PUNK_ENGINE_API void DestroyDefaultLogger();
}
PUNK_ENGINE_END

#endif // LOGGER_INTERFACE_H
