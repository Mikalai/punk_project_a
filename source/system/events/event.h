#ifndef EVENT_H
#define EVENT_H

#include "config.h"
#include "event_type.h"
#include "string/string.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API Event
    {
    public:
        int eventCode;
        void* anyData;
        void* reciever;

        virtual ~Event() {}

        virtual const Core::String ToString() const
        {
            return Core::String("Code: {0}; NO_DESCRIPTION").arg(eventCode);
        }
    };
}
PUNK_ENGINE_END

#endif // EVENT_H
