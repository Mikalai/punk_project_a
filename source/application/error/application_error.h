#ifndef APPLICATION_ERROR_H
#define APPLICATION_ERROR_H

#include <system/errors/module.h>

PUNK_ENGINE_BEGIN
namespace Runtime {
    namespace Error {
        class RuntimeError : public System::Error::SystemException {
            using System::Error::SystemException::SystemException;
        };
    }
}
PUNK_ENGINE_END

#endif // APPLICATION_ERROR_H
