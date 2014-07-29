#ifndef _H_FILE_CONSUMER
#define _H_FILE_CONSUMER

#include "log_consumer.h"


PUNK_ENGINE_BEGIN
namespace System {
	PUNK_ENGINE_LOCAL ILogConsumer* GetFileConsumer();
}
PUNK_ENGINE_END

#endif // _H_FILE_CONSUMER
