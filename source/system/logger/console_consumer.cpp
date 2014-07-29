#include <iostream>
#include <string/buffer.h>
#include "system/input/console.h"
#include "log_consumer.h"

PUNK_ENGINE_BEGIN

namespace System
{
	class PUNK_ENGINE_LOCAL ConsoleConsumer : public ILogConsumer
	{
	public:
		void Write(const Core::String& time, const Core::String& level, const Core::String &message) override {
			std::wstring _time{ (const wchar_t*)time.Data(), time.Length() };
			std::wstring _level{ (const wchar_t*)level.Data(), level.Length() };
			std::wstring _message{ (const wchar_t*)message.Data(), message.Length() };

			std::wcout << _time.c_str() << L'\t' << _level.c_str() << L'\t' << _message.c_str() << std::endl;
		}
	};

	PUNK_ENGINE_LOCAL ILogConsumer* GetConsoleConsumer() {
		return new ConsoleConsumer;
	}
}

PUNK_ENGINE_END
