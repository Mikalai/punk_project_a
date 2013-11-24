#ifndef _H_PUNK_SYSTEM_EXCEPTIONS
#define _H_PUNK_SYSTEM_EXCEPTIONS

#include "error/module.h"
#include "string/string.h"

namespace Punk {
    namespace Engine {
        namespace System {
            namespace Error {
                class PUNK_ENGINE_API SystemException : public Core::Error::Exception {
                public:
                    SystemException(std::uint64_t code);
                    const Core::String& GetStack() const { return m_stack; }
                private:
                    Core::String m_stack;
                };

                class PUNK_ENGINE_API PunkInvalidArgumentException : public SystemException {
                    using SystemException::SystemException;
                };

                class PUNK_ENGINE_API PunkInvalidCastException : public SystemException {
                    using SystemException::SystemException;
                };

                class PUNK_ENGINE_API PunkNotInitializedException : public SystemException {
                    using SystemException::SystemException;
                };

                class PUNK_ENGINE_API PunkNotImplemented : public SystemException {
                    using SystemException::SystemException;
                };

                class PUNK_ENGINE_API OSException : public SystemException {
                    using SystemException::SystemException;
                };
            }
        }
    }
}
#endif	//	_H_PUNK_SYSTEM_EXCEPTIONS
