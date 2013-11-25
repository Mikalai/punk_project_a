#ifndef _H_PUNK_IMAGE_EXCEPTIONS
#define _H_PUNK_IMAGE_EXCEPTIONS

#include "system/errors/module.h"

PUNK_ENGINE_BEGIN
namespace Image
{
    namespace Error {
        class PUNK_ENGINE_API ImageException : public System::Error::SystemException {
            using System::Error::SystemException::SystemException;
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_IMAGE_EXCEPTIONS
