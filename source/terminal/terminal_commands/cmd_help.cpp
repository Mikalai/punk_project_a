#include <string/module.h>
#include <terminal/command_processor.h>
#include "cmd_help.h"

PUNK_ENGINE_BEGIN
namespace Core {

	const String cmd_help_name = "help";
	HelpCommand::HelpCommand()
		: Command(cmd_help_name, "help cmd1 cmd2 ...", "Retrieve a description of the command") {}

	const String HelpCommand::Process(const StringList& args) {		
		if (args.Size() == 1 && args[0] == cmd_help_name) {
			CommandProcessor* proc = GetCommandProcessor();
			if (!proc)
				return "error";
            Command* cmd = proc->GetCommand(args[1]);
			if (!cmd)
				return "error";
            return cmd->Process(StringList("--help"));
		}
		else if (args.Size() > 1) {
			StringList list;
			CommandProcessor* proc = GetCommandProcessor();
            for (std::uint32_t index = 1; index < args.Size(); ++index) {
				Command* cmd = proc->GetCommand(args[index]);
				if (cmd)
                    list.Push(cmd->Process(StringList("--help")));
			}
			return list.ToString("\n");
		}
		return Command::Process(args);
	}
}
PUNK_ENGINE_END
