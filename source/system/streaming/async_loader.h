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
		void QueryInterface(std::uint64_t type, void** object) override;
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) = 0;
        virtual unsigned MainThreadProc(unsigned num_to_process) = 0;

        PUNK_OBJECT_DEFAULT_IMPL3(AsyncLoader)
    };
}
PUNK_ENGINE_END

#endif // ASYNC_LOADER_H
