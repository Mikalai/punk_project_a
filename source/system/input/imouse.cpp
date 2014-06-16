#include <array>
#include <memory.h>
#include <system/window/module.h>
#include <system/logger/module.h>
#include "imouse.h"

PUNK_ENGINE_BEGIN
namespace System
{
	class PUNK_ENGINE_LOCAL Mouse : public IMouse
	{
	public:

		Mouse();
		virtual ~Mouse();
		void QueryInterface(const Core::Guid& type, void** object) override;
		void Show(bool value) override;
		void LockInWindow(bool value) override;
		void SetButtonState(MouseButtons button, bool state) override;
		bool GetButtonState(MouseButtons button) const override;
		void BindCursorToWindow(IWindow* window) override;

		int GetGlobalX() const override;
		int GetGlobalY() const override;
		int GetLocalX() const override;
		int GetLocalY() const override;

		bool IsLocked() const override;
		bool IsVisible() const override;
		IWindow* GetBoundedWindow() const override;

	private:

		static const int MAX_MOUSE_BUTTONS{ 3 };
		std::array<bool, MAX_MOUSE_BUTTONS> m_buttons{ { false, false, false } };
		bool m_locked{ false };
		bool m_visible{ true };
		IWindow* m_region{ nullptr };

		PUNK_OBJECT_DEFAULT_IMPL(Mouse)
	};

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
	{
        GetDefaultLogger()->Info("Mouse created");
	}

    Mouse::~Mouse()
    {
        GetDefaultLogger()->Info("Mouse destroyed");
    }

    void Mouse::SetButtonState(MouseButtons button, bool state)
	{
        m_buttons[(int)button] = state;
	}

    bool Mouse::GetButtonState(MouseButtons button) const
	{
        return m_buttons[(int)button];
	}

	void Mouse::BindCursorToWindow(IWindow* window)
	{
        m_region = window;
	}

	void Mouse::LockInWindow(bool value)
	{
        m_locked = value;
	}

	void Mouse::Show(bool value)
	{
        (void)value;
#ifdef _WIN32
        ShowCursor(m_visible = value);
#endif
	}

	bool Mouse::IsLocked() const
	{
        return m_locked;
	}

	bool Mouse::IsVisible() const
	{
        return m_visible;
	}

	IWindow* Mouse::GetBoundedWindow() const
	{
        return m_region;
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
        if (m_region == 0)
			return p.x;
        return p.x - m_region->GetX();
#endif
        return 0;
	}

	int Mouse::GetLocalY() const
	{
#ifdef _WIN32
		POINT p;
		GetCursorPos(&p);
        if (m_region == 0)
			return p.y;
        return p.y - m_region->GetY();
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
