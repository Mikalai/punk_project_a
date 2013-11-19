#ifndef ASYNC_LOADER_H
#define ASYNC_LOADER_H

#include "config.h"
#include "system/core/object.h"

namespace System
{
    class AbstractDataLoader;
    class AbstractDataProcessor;

    class PUNK_ENGINE_API AsyncLoader : public Object
    {
    public:
        AsyncLoader();
        virtual ~AsyncLoader();
        virtual int AddWorkItem(AbstractDataLoader* loader, AbstractDataProcessor* processor, unsigned* result) = 0;
        virtual unsigned MainThreadProc(unsigned num_to_process) = 0;

        PUNK_OBJECT_ABSTRACT(AsyncLoader)
    };
}

#endif // ASYNC_LOADER_H
