#ifndef _H_PUNK_TERMINAL_COMMAND_PROCESSOR
#define _H_PUNK_TERMINAL_COMMAND_PROCESSOR

#include <config.h>
#include <string/string.h>
#include <map>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
	class IComponent;
    class Command;

	class PUNK_ENGINE_LOCAL CommandProcessor {
	public:
		void RegisterComponent(IComponent* component);
		void UnregisterComponent(IComponent* component);
        void UnregisterComponent(const String& component);
		IComponent* FindComponent(const String& name);
		void Process(const String& command);
        const std::map<String, Command*>& GetCommands();
        Command* GetCommand(const String& name);
        void RegisterCommand(Command* cmd);
        void UnregisterCommand(Command* cmd);

	private:
		std::map<String, IComponent*> m_components;
        std::map<String, Command*> m_commands;
	};

	extern "C" PUNK_ENGINE_API void RegisterComponent(IComponent* value);
	extern "C" PUNK_ENGINE_API void UnregisterComponent(IComponent* value);
	extern "C" PUNK_ENGINE_API IComponent* FindComponent(const String& value);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_TERMINAL_COMMAND_PROCESSOR
