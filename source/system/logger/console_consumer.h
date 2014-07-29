#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "log_consumer.h"

PUNK_ENGINE_BEGIN
namespace System {

	PUNK_ENGINE_LOCAL ILogConsumer* GetConsoleConsumer();
}
PUNK_ENGINE_END

#endif // CONSOLE_LOGGER_H
