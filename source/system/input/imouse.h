#ifndef MOUSE_INTERFACE_H
#define MOUSE_INTERFACE_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System
{
    class Window;
    enum class MouseButtons { LeftButton = 0, RightButton, MiddleButton };

	static const Core::Guid IID_IMouse{ "CCC4818A-8BB3-4713-8DD1-006411F62EF0" };

	class IMouse : public Core::IObject
    {
    public:
        virtual void Show(bool value) = 0;
        virtual void LockInWindow(bool value) = 0;
        virtual void SetButtonState(MouseButtons button, bool state) = 0;
        virtual bool GetButtonState(MouseButtons button) const = 0;
        virtual void BindCursorToWindow(Window* window) = 0;

        virtual int GetGlobalX() const = 0;
        virtual int GetGlobalY() const = 0;
        virtual int GetLocalX() const = 0;
        virtual int GetLocalY() const = 0;

        virtual bool IsLocked() const = 0;
        virtual bool IsVisible() const = 0;
        virtual Window* GetBoundedWindow() const = 0;
    };

    IMouse* GetMouse();
}
PUNK_ENGINE_END

#endif // MOUSE_INTERFACE_H
