#include <iostream>
#include "string/buffer.h"
#include "system/input/console.h"
#include "console_logger.h"

PUNK_ENGINE_BEGIN

namespace System
{
    ConsoleLogger::ConsoleLogger() {}

    ConsoleLogger::~ConsoleLogger() {}

    void ConsoleLogger::Write(const Core::String &value) {
        std::wcout << (const wchar_t*)value.Data() << std::endl;
    }
}

PUNK_ENGINE_END
