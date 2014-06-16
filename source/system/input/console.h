#ifndef _H_SYSTEM_CONSOLE
#define _H_SYSTEM_CONSOLE

#include <memory>
#include "iconsole.h"

#ifdef _WIN32
#include <Windows.h>
#endif

PUNK_ENGINE_BEGIN
namespace System
{
	class PUNK_ENGINE_LOCAL Console : public IConsole
	{
	public:
		Console();
        virtual ~Console();		
		void QueryInterface(const Core::Guid& type, void** object) override;
		//	set new cursor position in console
		void SetPosition(int x, int y) override;
		//	set new text color
		void SetTextColor(ConsoleColor col) override;
		//	set new back color
		void SetBackColor(ConsoleColor col) override;
		//	retreive console screen buffer width
		int GetScreenBufferWidth() const override;
		//	retrieve console screen buffer height
		int GetScreenBufferHeight() const override;
		//	retrieve visible width of the console screen
		int GetViewportWidth() override;
		//	retrieve visisble height of the console screen
		int GetViewportHeight() override;
		//	fills console with back color
		void Clear() override;
		void Write(const Core::String& value) override;
		const Core::String Read() override;

	private:
#ifdef _WIN32
		//	handle of the console object
		HANDLE m_console_handle;
		//	current cursor position
		COORD m_cursor_position;
		//	selected text color
		WORD m_text_color;
		//	selected back color
		WORD m_back_color;
		//	information of the console screen buffer
		CONSOLE_SCREEN_BUFFER_INFO m_screen_info;
#elif defined __gnu_linux__
		int m_x, m_y;
#endif

		PUNK_OBJECT_DEFAULT_IMPL(Console)
	};
}
PUNK_ENGINE_END

#endif	//	_H_SYSTEM_CONSOLE
