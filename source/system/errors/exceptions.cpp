#include "exceptions.h"
#include "stack_trace.h"

namespace Punk {
    namespace Engine {
        namespace System {
            namespace Error {

                SystemException::SystemException(const Core::String& msg, std::uint64_t code)
                    : Core::Error::Exception(code)
                    , m_message(msg)
                {
                    Stack stack;
                    m_stack = stack.GetStackTrace();
                }
            }
        }
    }
}
