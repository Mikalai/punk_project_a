#ifndef _H_PUNK_SYSTEM_MOUSE
#define _H_PUNK_SYSTEM_MOUSE

#include "core/object.h"
#include "mouse_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    namespace __private {
        struct MouseImpl;
    }

    class PUNK_ENGINE_API Mouse : public IMouse, public Core::Object
	{
	public:        

	public:

		Mouse();
        virtual ~Mouse();
        void Show(bool value) override;
        void LockInWindow(bool value) override;
        void SetButtonState(MouseButtons button, bool state) override;
        bool GetButtonState(MouseButtons button) const override;
        void BindCursorToWindow(Window* window) override;

        int GetGlobalX() const override;
        int GetGlobalY() const override;
        int GetLocalX() const override;
        int GetLocalY() const override;
		
        bool IsLocked() const override;
        bool IsVisible() const override;
        Window* GetBoundedWindow() const override;

        __private::MouseImpl* impl;

        PUNK_OBJECT(Mouse)
	};
}
PUNK_ENGINE_END

#endif
