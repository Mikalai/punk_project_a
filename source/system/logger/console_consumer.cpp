#include <iostream>
#include "string/buffer.h"
#include "system/input/console.h"
#include "console_consumer.h"

PUNK_ENGINE_BEGIN

namespace System
{
    ConsoleConsumer::ConsoleConsumer() {}

    ConsoleConsumer::~ConsoleConsumer() {}

    void ConsoleConsumer::Write(const Core::String &value) {
        std::wcout << (const wchar_t*)value.Data() << std::endl;
    }
}

PUNK_ENGINE_END
