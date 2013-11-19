#include "punk_error.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            namespace Error {

                Exception::Exception(std::uint64_t code)
                    : m_code(code) {}

                std::uint64_t Exception::GetCode() const {
                    return m_code;
                }
            }
        }
    }
}
