#ifndef _H_PUNK_STACK_TRACE_WIN32
#define _H_PUNK_STACK_TRACE_WIN32

#include <config.h>
#include <String/String.h>

namespace Punk {
    namespace Engine {
        namespace System {
            class PUNK_ENGINE_API Stack
            {
            public:
                Stack();
                ~Stack();
                Core::String GetStackTrace();
            };
        }
    }
}

#endif	//_H_PUNK_STACK_TRACE_WIN32
