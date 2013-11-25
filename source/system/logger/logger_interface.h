#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include "config.h"
#include "core/action.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{    
    using LogEvent = Core::ActionBasePtr<const Core::String&>;

    class ILogger
    {
    public:
        virtual void Write(const Core::String& value) = 0;
        virtual void Connect(LogEvent event) = 0;
    };
}
PUNK_ENGINE_END

PUNK_ENGINE_API Punk::Engine::System::ILogger& out_error();
PUNK_ENGINE_API Punk::Engine::System::ILogger& out_message();
PUNK_ENGINE_API Punk::Engine::System::ILogger& out_warning();

#ifdef _DEBUG
#define OUT_MESSAGE(X) out_message().Write(X);
#define OUT_WARNING(X) out_warning().Write(X);
#define OUT_ERROR(X)   out_error().Write(X);
#else
#define OUT_MESSAGE(X) out_message().Write(X);
#define OUT_WARNING(X) out_warning().Write(X);
#define OUT_ERROR(X)   out_error().Write(X);
#endif

#endif // LOGGER_INTERFACE_H
