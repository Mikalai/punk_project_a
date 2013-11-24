#ifndef _H_PUNK_SYSTEM_WINDOW
#define _H_PUNK_SYSTEM_WINDOW

#include <map>

#include "config.h"
#include "string/string.h"
#include "system/action.h"
#include "system/events/interface.h"
#include "core/object.h"
#include "window_description.h"

namespace Punk {
    namespace Engine {
        namespace System {

            class PUNK_ENGINE_API Window : public Object
            {
            public:
                Window();
                virtual ~Window();

                ActionSlot<const WindowResizeEvent&> OnResizeEvent;
                ActionSlot<const KeyEvent&> OnKeyEvent;
                ActionSlot<const MouseEvent&> OnMouseEvent;
                ActionSlot<const MouseHooverEvent&> OnMouseHooverEvent;
                ActionSlot<const MouseWheelEvent&> OnMouseWheelEvent;

                virtual int GetDesktopWidth() const = 0;
                virtual int GetDesktopHeight() const = 0;
                virtual int GetDesktopBitsPerPixel() const = 0;
                virtual int GetDesktopRefreshRate() const = 0;
                virtual int GetWidth() const = 0;
                virtual int GetHeight() const = 0;
                virtual int GetX() const = 0;
                virtual int GetY() const = 0;
                virtual void SetSize(int width, int height) = 0;
                virtual void SetPosition(int x, int y) = 0;
                virtual int Loop() = 0;
                virtual void BreakMainLoop() = 0;
                virtual void SetTitle(const string& text) = 0;
                virtual const string GetTitle() const = 0;
                virtual void Quite() = 0;
                virtual void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
                virtual void DrawLine(int x1, int y1, int x2, int y2) = 0;
                virtual void ShowCursor(bool value) = 0;

                PUNK_OBJECT_ABSTRACT(Window)
            };

            PUNK_ENGINE_API Window* CreateRootWindow(const WindowDesc& desc);
        }
    }
}

#endif	//_H_PUNK_SYSTEM_WINDOW
