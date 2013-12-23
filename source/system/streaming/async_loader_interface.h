#ifndef ASYNC_LOADER_INTERFACE_H
#define ASYNC_LOADER_INTERFACE_H

#include <config.h>
#include "data_loader.h"
#include "data_processor.h"

PUNK_ENGINE_BEGIN
namespace System {

    class IAsyncLoader {
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) = 0;
        virtual unsigned MainThreadProc(unsigned num_to_process) = 0;
    };

    extern "C" PUNK_ENGINE_API IAsyncLoader* CreateAsyncLoader(int num_threads);
    extern "C" PUNK_ENGINE_API void DestroyAsyncLoader(IAsyncLoader* value);
}

PUNK_ENGINE_END

#endif // ASYNC_LOADER_INTERFACE_H
