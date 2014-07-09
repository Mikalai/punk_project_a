#include <sstream>
#include <iostream>
#include <string/buffer.h>
#include <system/errors/module.h>
#include "system/input/console.h"
#include "file_consumer.h"

PUNK_ENGINE_BEGIN

namespace System
{
#ifdef _WIN32
	std::uint32_t GetPid() {
		return (std::uint32_t)GetCurrentProcessId();
	}
#endif

	FileConsumer::FileConsumer() {
		std::wstringstream stream;
		stream << L"_" << GetPid() << L".log";
		auto file = stream.str();
		m_stream.open(file);
		if (!m_stream.is_open()) {
			std::cout << "Can't open log file" << std::endl;
			exit(0);
		}
	}

	FileConsumer::~FileConsumer() {}

	void FileConsumer::Write(const Core::String &value) {
		std::wstring s{ (const wchar_t*)value.Data(), value.Length() };
		m_stream << s << std::endl;
	}
}

PUNK_ENGINE_END
