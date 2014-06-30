#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include "config.h"
#include <string/string.h>
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
        virtual void IncreaseOffset() = 0;
        virtual void DescreaseOffset() = 0;
    };

    extern PUNK_ENGINE_API ILogger* GetDefaultLogger();
    extern PUNK_ENGINE_API void DestroyDefaultLogger();

#ifdef _DEBUG
    namespace __private {
        struct PUNK_ENGINE_API LogScope {
            LogScope(const Core::String& scope);
            ~LogScope();
        private:
            const Core::String m_scope;
        };
    }

#ifdef WIN32
#define LOG_FUNCTION_SCOPE //System::__private::LogScope __scope(__FUNCSIG__)
#elif defined __linux__
#define LOG_FUNCTION_SCOPE System::__private::LogScope __scope(Core::String(__PRETTY_FUNCTION__))// + L" in " + Core::String(__FILE__) + L": " + Core::String::Convert(__LINE__));
#endif

#define LOG_SCOPE(MESSAGE) //System::__private::LogScope __scope(MESSAGE)

#else
#define LOG_FUNCTION_SCOPE
#define LOG_SCOPE(MESSAGE)
#endif
}
PUNK_ENGINE_END

#endif // LOGGER_INTERFACE_H
