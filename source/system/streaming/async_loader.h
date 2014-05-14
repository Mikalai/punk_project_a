#ifndef ASYNC_LOADER_H
#define ASYNC_LOADER_H

#include "config.h"
#include "async_loader_interface.h"
#include "core/object.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class AbstractDataLoader;
    class AbstractDataProcessor;

    class PUNK_ENGINE_LOCAL AsyncLoader : public IAsyncLoader
    {
    public:
        AsyncLoader();
        virtual ~AsyncLoader();
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) = 0;
        virtual unsigned MainThreadProc(unsigned num_to_process) = 0;

        PUNK_OBJECT_DEFAULT_IMPL(AsyncLoader)
    };
}
PUNK_ENGINE_END

#endif // ASYNC_LOADER_H
