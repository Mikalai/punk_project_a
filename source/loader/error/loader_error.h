#ifndef LOADER_ERROR_H
#define LOADER_ERROR_H

#include <system/errors/module.h>

PUNK_ENGINE_BEGIN
namespace Loader {
    namespace Error {
        class LoaderException : System::Error::SystemException {
            using System::Error::SystemException::SystemException;
        };
    }
}
PUNK_ENGINE_END

#endif // LOADER_ERROR_H
