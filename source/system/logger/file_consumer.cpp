#include <sstream>
#include <iostream>
#include <system/factory/module.h>
#include <string/buffer.h>
#include <system/errors/module.h>
#include "system/input/console.h"
#include <fstream>
#include "log_consumer.h"

PUNK_ENGINE_BEGIN

namespace System
{
#ifdef _WIN32
	std::uint32_t GetPid() {
		return (std::uint32_t)GetCurrentProcessId();
	}
#endif


	class PUNK_ENGINE_LOCAL FileConsumer : public ILogConsumer
	{
	public:
		FileConsumer() {
            std::stringstream stream;
            stream << L"_" << GetPid() << ".log";
			auto file = stream.str();
            m_stream.open(file);
			if (!m_stream.is_open()) {
				std::cout << "Can't open log file" << std::endl;
				exit(0);
			}
		}

		~FileConsumer() {}

		void Write(const Core::String& time, const Core::String& level, const Core::String &message) override {
			std::wstring _time{ (const wchar_t*)time.Data(), time.Length() };
			std::wstring _level{ (const wchar_t*)level.Data(), level.Length() };
			std::wstring _message{ (const wchar_t*)message.Data(), message.Length() };
			m_stream << _time << L'\t' << _level << L'\t' << _message << std::endl;
		}
	
	private:
		std::wofstream m_stream;
	};	

	PUNK_ENGINE_LOCAL ILogConsumer* GetFileConsumer() {
		return new FileConsumer();
	}
}

PUNK_ENGINE_END
