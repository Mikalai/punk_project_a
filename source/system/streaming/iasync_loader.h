#ifndef ASYNC_LOADER_INTERFACE_H
#define ASYNC_LOADER_INTERFACE_H

#include <config.h>
#include <core/iobject.h>
#include "data_loader.h"
#include "data_processor.h"

PUNK_ENGINE_BEGIN
namespace System {

	static const Core::Guid IID_IAsyncLoader{ "1A9DA15D-7147-416A-8F5B-AF48D9ECF7B6" };

    class IAsyncLoader : public Core::IObject {
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) = 0;
        virtual unsigned MainThreadProc(unsigned num_to_process) = 0;
    };

    extern PUNK_ENGINE_API IAsyncLoader* CreateAsyncLoader(int num_threads);
    extern PUNK_ENGINE_API void DestroyAsyncLoader(IAsyncLoader* value);
}

PUNK_ENGINE_END

#endif // ASYNC_LOADER_INTERFACE_H
