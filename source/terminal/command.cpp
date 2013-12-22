#include <string/module.h>
#include "command_processor.h"
#include "command.h"

PUNK_ENGINE_BEGIN
namespace Core {
	static const String Register = "register";
	static const String Unregister = "unregister";

	Command::Command(const String& name, const String& usage, const String& description)
		: m_name{ new String{ name } }
		, m_usage{ new String{ usage } }
		, m_description{ new String{ description } }
	{}

	Object* Command::Process(const StringList& params, Object** args) {
		if (params.Size() < 2 || args == nullptr)
			return nullptr;
		if (params[1] == Register) {
			CommandProcessor* p = Cast<CommandProcessor*>(args[0]);
			if (!p)
				return nullptr;
			m_processor = p;
		}
		else if (params[1] == Unregister) {			
			m_processor = nullptr;
		}
	}

	const String Command::Process(const StringList& args) {
		if (args.Size() < 2)
			return "";
		if (args[1] == "--help" || args[1] == "-h") {
			return String("{0}\n{1}\n{2}").arg(*m_name).arg(*m_usage).arg(*m_description);
		}
	}

	Command::~Command() {
		delete m_name;
		delete m_description;
		delete m_usage;
	}
}
PUNK_ENGINE_END