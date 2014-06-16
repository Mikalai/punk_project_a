#ifndef CORE_ERROR_H
#define CORE_ERROR_H

#include <error/module.h>
#include "String/String.h"

PUNK_ENGINE_BEGIN
namespace Core {
    namespace Error {
    class PUNK_ENGINE_API CoreException : public Exception {
    public:
        CoreException(const String& value, std::uint32_t code = 0);
        const String& GetData() const { return m_data; }
    public:
        String m_data;
    };
    }
}
PUNK_ENGINE_END

#endif // CORE_ERROR_H
