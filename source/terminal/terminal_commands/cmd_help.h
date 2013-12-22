#ifndef _H_PUNK_TERMINAL_CMD_HELP
#define _H_PUNK_TERMINAL_CMD_HELP

#include <config.h>
#include <terminal/command.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class PUNK_ENGINE_LOCAL HelpCommand : public Command {
	public:		
		HelpCommand();
		virtual ~HelpCommand() {}
		virtual const String Process(const StringList& params);
	private:
	};
}
PUNK_ENGINE_END
#endif	//	_H_PUNK_TERMINAL_CMD_HELP