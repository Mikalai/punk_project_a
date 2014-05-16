#ifndef _H_SYSTEM_ICONSOLE
#define _H_SYSTEM_ICONSOLE

#include <memory>
#include <config.h>
#include <string/string.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System
{
	//	possible colors that can be use in console
	enum class ConsoleColor {
		COLOR_BLACK,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_CYAN,
		COLOR_RED,
		COLOR_MAGENTA,
		COLOR_BROWN,
		COLOR_LIGHTGRAY,
		COLOR_DARKGRAY,
		COLOR_LIGHTBLUE,
		COLOR_LIGHTGREEN,
		COLOR_LIGHTCYAN,
		COLOR_LIGHTRED,
		COLOR_LIGHTMAGENTA,
		COLOR_YELLOW,
		COLOR_WHITE
	};

	static const Core::Guid IID_IConsole{ "8F529ECF-9924-4562-87D6-25E144DFEFC8" };
	class IConsole : public virtual Core::IObject
	{
	public:		
		//	set new cursor position in console
		virtual void SetPosition(int x, int y) = 0;
		//	set new text color
		virtual void SetTextColor(ConsoleColor col) = 0;
		//	set new back color
		virtual void SetBackColor(ConsoleColor col) = 0;
		//	retreive console screen buffer width
		virtual int GetScreenBufferWidth() const = 0;
		//	retrieve console screen buffer height
		virtual int GetScreenBufferHeight() const = 0;
		//	retrieve visible width of the console screen
		virtual int GetViewportWidth() = 0;
		//	retrieve visisble height of the console screen
		virtual int GetViewportHeight() = 0;
		//	fills console with back color
		virtual void Clear() = 0;		
		virtual void Write(const Core::String& value) = 0;
		virtual const Core::String Read() = 0;
	};

	extern PUNK_ENGINE_API IConsole* GetDefaultConsole();
}
PUNK_ENGINE_END

#endif	//	_H_SYSTEM_ICONSOLE
