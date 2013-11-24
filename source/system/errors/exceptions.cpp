#include "exceptions.h"
#include "stack_trace.h"

namespace Punk {
    namespace Engine {
        namespace System {
            namespace Error {

                SystemException::SystemException(std::uint64_t code)
                    : Core::Error::Exception(code)
                {
                    Stack stack;
                    m_stack = stack.GetStackTrace();
                }
            }
        }
    }
}
