#include <memory.h>
#include "mouse.h"
#include "system/window/module.h"
#include "system/logger/module.h"

PUNK_ENGINE_BEGIN
namespace System
{
    namespace __private {
        struct MouseImpl {
            MouseImpl()
                : m_region(0) {
                memset(m_buttons, 0, sizeof(m_buttons));
            }

            static const int MAX_MOUSE_BUTTONS = 3;
            bool m_buttons[MAX_MOUSE_BUTTONS];
            bool m_locked;
            bool m_visible;
            Window* m_region;
        };
    }

	void Mouse::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == IID_IMouse) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

    Mouse::Mouse()
        : impl(new __private::MouseImpl)
	{
        GetDefaultLogger()->Info("Mouse created");
	}

    Mouse::~Mouse()
    {
        delete impl;
        impl = nullptr;        
        GetDefaultLogger()->Info("Mouse destroyed");
    }

    void Mouse::SetButtonState(MouseButtons button, bool state)
	{
        impl->m_buttons[(int)button] = state;
	}

    bool Mouse::GetButtonState(MouseButtons button) const
	{
        return impl->m_buttons[(int)button];
	}

	void Mouse::BindCursorToWindow(Window* window)
	{
        impl->m_region = window;
	}

	void Mouse::LockInWindow(bool value)
	{
        impl->m_locked = value;
	}

	void Mouse::Show(bool value)
	{
        (void)value;
#ifdef _WIN32
        ShowCursor(impl->m_visible = value);
#endif
	}

	bool Mouse::IsLocked() const
	{
        return impl->m_locked;
	}

	bool Mouse::IsVisible() const
	{
        return impl->m_visible;
	}

	Window* Mouse::GetBoundedWindow() const
	{
        return impl->m_region;
	}

	int Mouse::GetGlobalX() const
	{
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
		return p.x;
#endif
#ifdef __gnu_linux__
        return 0;
#endif
	}

	int Mouse::GetGlobalY() const
	{
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
		return p.y;
#endif
        return 0;
	}

	int Mouse::GetLocalX() const
	{
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
        if (impl->m_region == 0)
			return p.x;
        return p.x - impl->m_region->GetX();
#endif
        return 0;
	}

	int Mouse::GetLocalY() const
	{
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
        if (impl->m_region == 0)
			return p.y;
        return p.y - impl->m_region->GetY();
#endif
        return 0;
	}

    IMouse* GetMouse() {
        static Mouse* g_mouse;
        if (!g_mouse)
            g_mouse = new Mouse;
        return g_mouse;
    }
}
PUNK_ENGINE_END
