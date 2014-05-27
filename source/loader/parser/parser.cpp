#include <memory>
#include <system/logger/module.h>
#include "parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule {
	std::unique_ptr<Parser> g_parser;

	Parser* GetDefaultParser() {
		if (!g_parser.get())
			g_parser.reset(new Parser);
		return g_parser.get();
	}

	void Parser::AddParser(KeywordCode code, ParseFunction parser) {
		try {
			System::GetDefaultLogger()->Info("Add parser for " + GetKeyword(code));
			m_parser[code] = parser;
		}
		catch (Error::LoaderException& e) {
			System::GetDefaultLogger()->Error("Failed to register parser. " + e.Message() + ". " + e.GetStack());
		}
	}

	void Parser::RemoveParser(KeywordCode code) {
		auto it = m_parser.find(code);
		if (it == m_parser.end()) {
			System::GetDefaultLogger()->Warning("Can't remove parser for " + GetKeyword(code) + ", because it was not registered");
			return;
		}
		m_parser.erase(it);
	}

	void Parser::Parse(KeywordCode code, Core::Buffer& buffer, void* object) {
		auto it = m_parser.find(code);
		if (it == m_parser.end()) {
			throw Error::LoaderException("Parser not registered for " + GetKeyword(code));
		}
		it->second(buffer, object);
	}
}
PUNK_ENGINE_END
