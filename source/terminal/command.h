#ifndef _H_PUNK_TERMINAL_COMMAND
#define _H_PUNK_TERMINAL_COMMAND

#include <config.h>
#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class StringList;
	class String;
	class CommandProcessor;

    class PUNK_ENGINE_API Command : public Object {
	public:				
        Command(const String& name, const String& usage, const String& description);
        Command(const Command&) = delete;
        Command& operator = (const Command&) = delete;
        virtual ~Command();
		virtual Object* Process(const StringList& params, Object** args);	
		virtual const String Process(const StringList& params);
	protected:
		CommandProcessor* GetCommandProcessor() { return m_processor; }

	private:
		CommandProcessor* m_processor;
		String* m_name;
		String* m_description;
		String* m_usage;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_TERMINAL_COMMAND
