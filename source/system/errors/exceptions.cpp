#include "exceptions.h"
#include <system/dbg/stack_trace.h>

PUNK_ENGINE_BEGIN
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
PUNK_ENGINE_END
