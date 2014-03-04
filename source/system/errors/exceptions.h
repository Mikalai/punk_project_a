#ifndef _H_PUNK_SYSTEM_EXCEPTIONS
#define _H_PUNK_SYSTEM_EXCEPTIONS

#include "error/module.h"
#include "string/string.h"

PUNK_ENGINE_BEGIN
namespace System {
    namespace Error {
        class PUNK_ENGINE_API SystemException : public Core::Error::Exception {
        public:
            SystemException(const Core::String& msg, std::uint64_t code = 0);
            const Core::String& GetStack() const { return m_stack; }
            const Core::String& Message() const { return m_message; }
        private:
            Core::String m_message;
            Core::String m_stack;
        };

        class PUNK_ENGINE_API InvalidArgumentException : public SystemException {
            using SystemException::SystemException;
        };

        class PUNK_ENGINE_API InvalidCastException : public SystemException {
            using SystemException::SystemException;
        };

        class PUNK_ENGINE_API NotInitializedException : public SystemException {
            using SystemException::SystemException;
        };

        class PUNK_ENGINE_API NotImplemented : public SystemException {
            using SystemException::SystemException;
        };

        class PUNK_ENGINE_API OSException : public SystemException {
            using SystemException::SystemException;
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_EXCEPTIONS
