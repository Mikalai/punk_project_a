#ifndef CORE_ERROR_H
#define CORE_ERROR_H

#include "error/module.h"
#include "string/string.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            namespace Error {
                class CoreException : public Exception {
                public:
                    CoreException(const String& value, std::uint32_t code = 0);
                    const String& GetData() const { return m_data; }
                public:
                    String m_data;
                };
            }
        }
    }
}

#endif // CORE_ERROR_H
