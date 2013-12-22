#include <core/component/component_interface.h>
#include <string/module.h>
#include "command_processor.h"
#include "command.h"

PUNK_ENGINE_BEGIN
namespace Core {
	CommandProcessor* g_processor;
	
	CommandProcessor* GetProcessor() {
		if (!g_processor)
			g_processor = new CommandProcessor;
		return g_processor;
	}

	static const String GetTerminalCommandsCount = "get_terminal_commands_count";
	static const String GetTerminalCommand = "get_terminal_command {0}";
	static const String GetName = "get_name";

	void CommandProcessor::RegisterComponent(IComponent* component) {
		int commands_count = component->Execute(GetTerminalCommandsCount).ToInt32();
		for (int i = 0; i < commands_count; ++i) {
            Object* o = component->Execute(String(GetTerminalCommand).arg(i), nullptr);
            Command* command = Cast<Command*>(o);
			RegisterCommand(command);
		}
	}

    void CommandProcessor::RegisterCommand(Command* command) {
		if (command) {
			m_commands[command->Process(GetName)] = command;
		}
	}

    void CommandProcessor::UnregisterCommand(Command* command) {
		if (command) {
			auto it = m_commands.find(command->Process(GetName));
			if (it != m_commands.end())
				m_commands.erase(it);
		}
	}

	void CommandProcessor::UnregisterComponent(IComponent* component) {
		int commands_count = component->Execute(GetTerminalCommandsCount).ToInt32();
		for (int i = 0; i < commands_count; ++i) {
			Object* o = component->Execute(String(GetTerminalCommand).arg(i), nullptr);
            Command* command = Cast<Command*>(o);
			UnregisterCommand(command);
		}
	}

    Command* CommandProcessor::GetCommand(const String& name) {
        try {
            return m_commands.at(name);
        }
        catch(...) {
            return nullptr;
        }
    }

	IComponent* CommandProcessor::FindComponent(const String& name) {
		try {
            return m_components.at(name);
		}
		catch (...) {
			return nullptr;
		}
	}

	void RegisterComponent(IComponent* value) {
		GetProcessor()->RegisterComponent(value);
	}

	void UnregisterComponent(IComponent* value) {
		GetProcessor()->UnregisterComponent(value);
	}

	IComponent* FindComponent(const String& value) {
		return GetProcessor()->FindComponent(value);
	}
}
PUNK_ENGINE_END
