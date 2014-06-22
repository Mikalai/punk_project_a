#ifdef _WIN32
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <system/time/timer_interface.h>
#include <core/action.h>
#include "window_base.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
    LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    class PUNK_ENGINE_LOCAL WindowWin : public WindowBase
    {
    public:
        WindowWin();
        ~WindowWin();        

		void Initialize(const WindowDescription& desc) override;
		int GetDesktopWidth() const override;
		int GetDesktopHeight() const override;
		int GetDesktopBitsPerPixel() const override;
		int GetDesktopRefreshRate() const override;
		int GetWidth() const override;
		int GetHeight() const override;
		int GetX() const override;
		int GetY() const override;
		void SetSize(int width, int height) override;
		void SetPosition(int x, int y) override;
		int Update(int dt) override;
		int Loop() override;
		void BreakMainLoop() override;
		void SetTitle(const Core::String& text) override;
		const Core::String GetTitle() const override;
		void Quite() override;
		void ShowCursor(bool value) override;
		HWND GetNativeHandle() override;

    protected:

        void InternalCreate() override;
        void InternalDestroy() override;

    private:
        HWND m_hwindow;
        bool m_use_parent_window;
        WindowDescription m_window_description;
		ITimerUniquePtr m_timer{ nullptr, Core::DestroyObject };

        friend LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };	
}
PUNK_ENGINE_END

#endif // WIN32_WINDOW_H
#endif //_win32
