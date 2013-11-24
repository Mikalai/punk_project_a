#include "core_error.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            namespace Error {

                CoreException::CoreException(const String &value, std::uint32_t code)
                    : Exception(code)
                    , m_data(value) {}
            }
        }
    }
}
