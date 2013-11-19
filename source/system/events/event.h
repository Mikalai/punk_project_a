#ifndef EVENT_H
#define EVENT_H

#include "event_type.h"
#include <queue>
#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	class PUNK_ENGINE_API Event
    {
    public:
        int eventCode;        
		void* anyData;
		void* reciever;

		virtual ~Event() {}

        virtual const string ToString()
		{
            return string("Code: {0}; NO_DESCRIPTION").arg(eventCode);
		}
    };
}

#endif // EVENT_H
