#ifndef _H_PUNK_VIRTUAL_LOADER
#define _H_PUNK_VIRTUAL_LOADER

#include <map>
#include <loader/error/loader_error.h>
#include "keywords.h"

#define CHECK_START(buffer)\
    if (!IoModule::CheckIntegrity(buffer))\
{\
    throw Error::LoaderException(L"Integrity check failed");\
    }

#define CHECK_END(buffer)\
    if (IoModule::ParseKeyword(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
{\
    throw Error::LoaderException(L"Integrity check failed");\
    }

PUNK_ENGINE_BEGIN
namespace IoModule {
    extern bool CheckIntegrity(Core::Buffer& buffer);

	typedef bool (*ParseFunction)(Core::Buffer& buffer, void*);

	class Parser {
	public:
		void AddParser(KeywordCode code, ParseFunction parser);
		void RemoveParser(KeywordCode code);
		void Parse(KeywordCode code, Core::Buffer& buffer, void* object);

		template<class T>
		void Parse(KeywordCode code, Core::Buffer& buffer, T& object) {
			Parse(code, buffer, (void*)&object);
		}

		template<class T> 
		void Parse(KeywordCode code, Core::Buffer& buffer, T* object) {
			Parse(code, buffer, (void*)object);
		}

	private:
		std::map<KeywordCode, ParseFunction> m_parser;
	};

	Parser* GetDefaultParser();

	struct RegisterParser {
		RegisterParser(KeywordCode code, ParseFunction function) {
			GetDefaultParser()->AddParser(code, function);
		}
	};

#define PUNK_REGISTER_PARSER(Code, Func) static RegisterParser g_##Code{Code, Func}

}
PUNK_ENGINE_END

#endif
