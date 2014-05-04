#ifdef _WIN32
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <system/time/timer_interface.h>
#include <core/action.h>
#include "window.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
    LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    class PUNK_ENGINE_API WindowWin : public Window
    {
    public:
        WindowWin(const WindowDescription& desc = WindowDescription());
        ~WindowWin();        

        int GetDesktopWidth() const;
        int GetDesktopHeight() const;
        int GetDesktopBitsPerPixel() const;
        int GetDesktopRefreshRate() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        void SetSize(int width, int height);
        void SetPosition(int x, int y);
		int Update(int dt) override;
        int Loop();
        void BreakMainLoop();
        void SetTitle(const Core::String& text);
        const Core::String GetTitle() const;
        void Quite();
        void ShowCursor(bool value);
        operator HWND ();

    protected:

        void InternalCreate() override;
        void InternalDestroy() override;

    private:
        HWND m_hwindow;
        bool m_use_parent_window;
        WindowDescription m_window_description;
		ITimerUniquePtr m_timer{ nullptr, DestroyTimer };

        friend LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };
}
PUNK_ENGINE_END

#endif // WIN32_WINDOW_H
#endif //_win32
