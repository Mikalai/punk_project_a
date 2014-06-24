#ifdef __gnu_linux__
//#include <GL/glx.h>
#include <X11/keysym.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include <core/ifactory.h>
#include "system/errors/module.h"
#include "system/events/module.h"
#include "system/logger/module.h"
#include "system/time/module.h"
#include "x11_window.h"

typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPbuffer;
typedef XID GLXPixmap;
typedef XID GLXWindow;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXDrawable;
typedef XID GLXContextID;


PUNK_ENGINE_BEGIN
namespace System
{
    WindowX11::WindowX11()
    { }

    void WindowX11::Initialize(const WindowDescription &desc) {
        m_window_description = desc;
    }

    WindowX11::~WindowX11()
    {        
    }

    int WindowX11::GetDesktopWidth() const
    {
        return 0;//WidthOfScreen(m_screen);
    }

    int WindowX11::GetDesktopHeight() const
    {
        return 0;//HeightOfScreen(m_screen);
    }

    int WindowX11::GetDesktopBitsPerPixel() const
    {
        auto screen = XDefaultScreenOfDisplay(m_display);
        return screen->root_visual->bits_per_rgb;
    }

    int WindowX11::GetDesktopRefreshRate() const
    {
        //auto screen = XDefaultScreenOfDisplay(m_display);
        return 0;
    }

    int WindowX11::GetWidth() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.width;
    }

    int WindowX11::GetHeight() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.height;
    }

    int WindowX11::GetX() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.x;
    }

    int WindowX11::GetY() const
    {
        XWindowAttributes attr;
        XGetWindowAttributes(m_display, m_window, &attr);
        return attr.y;
    }

    void WindowX11::SetSize(int width, int height)
    {
        XWindowChanges v;
        v.width = width;
        v.height = height;
        XConfigureWindow(m_display, m_window, CWWidth | CWHeight, &v);
    }

    void WindowX11::SetPosition(int x, int y)
    {
        XWindowChanges v;
        v.x = x;
        v.y = y;
        XConfigureWindow(m_display, m_window, CWX | CWY, &v);
    }

    int WindowX11::DecodeKey(KeySym keysym, int& charKey, bool press)
    {
        bool (*buttons)[256] = GetKeyboard()->GetKeyStates();    //  TODO: Something better should be here
        bool* m_buttons = *buttons;
        int key;
        switch (keysym)
        {
        case XK_Alt_L:
            m_buttons[(key = PUNK_KEY_LEFT_ALT)] = press;
            break;
        case XK_Alt_R:
            m_buttons[(key = PUNK_KEY_RIGHT_ALT)] = press;
            break;
        case XK_Tab:
            m_buttons[(key = PUNK_KEY_TAB)] = press;
            break;
        case XK_Caps_Lock:
            m_buttons[(key = PUNK_KEY_CAPSLOCK)] = press;
            break;
        case XK_Page_Up:
            m_buttons[(key = PUNK_KEY_PAGE_UP)] = press;
            break;
        case XK_Page_Down:
            m_buttons[(key = PUNK_KEY_PAGE_DOWN)] = press;
            break;
        case XK_Return:
            m_buttons[(key = PUNK_KEY_ENTER)] = press;
            break;
        case XK_Escape:
            m_buttons[(key = PUNK_KEY_ESCAPE)] = press;
            BreakMainLoop();
            break;
        case XK_space:
            charKey = ' ';
            m_buttons[(key = PUNK_KEY_SPACE)] = press;
            break;
        case XK_End:
            m_buttons[(key = PUNK_KEY_END)] = press;
            break;
        case XK_Home:
            m_buttons[(key = PUNK_KEY_HOME)] = press;
            break;
        case XK_Left:
            m_buttons[(key = PUNK_KEY_LEFT)] = press;
            break;
        case XK_Up:
            m_buttons[(key = PUNK_KEY_UP)] = press;
            break;
        case XK_Right:
            m_buttons[(key = PUNK_KEY_RIGHT)] = press;
            break;
        case XK_Down:
            m_buttons[(key = PUNK_KEY_DOWN)] = press;
            break;
        case XK_Insert:
            m_buttons[(key = PUNK_KEY_INSERT)] = press;
            break;
        case XK_Delete:
            m_buttons[(key = PUNK_KEY_DELETE)] = press;
            break;
        case XK_0:
            charKey = '0';
            m_buttons[(key = PUNK_KEY_0)] = press;
            break;
        case XK_1:
            charKey = '1';
            m_buttons[(key = PUNK_KEY_1)] = press;
            break;
        case XK_2:
            charKey = '2';
            m_buttons[(key = PUNK_KEY_2)] = press;
            break;
        case XK_3:
            charKey = '3';
            m_buttons[(key = PUNK_KEY_3)] = press;
            break;
        case XK_4:
            charKey = '4';
            m_buttons[(key = PUNK_KEY_4)] = press;
            break;
        case XK_5:
            charKey = '5';
            m_buttons[(key = PUNK_KEY_5)] = press;
            break;
        case XK_6:
            charKey = '6';
            m_buttons[(key = PUNK_KEY_6)] = press;
            break;
        case XK_7:
            charKey = '7';
            m_buttons[(key = PUNK_KEY_7)] = press;
            break;
        case XK_8:
            charKey = '8';
            m_buttons[(key = PUNK_KEY_8)] = press;
            break;
        case XK_9:
            charKey = '9';
            m_buttons[(key = PUNK_KEY_9)] = press;
            break;
        case XK_A:
            charKey = 'A';
            m_buttons[(key = PUNK_KEY_A)] = press;
            break;
        case XK_a:
            charKey = 'a';
            m_buttons[(key = PUNK_KEY_A)] = press;
            break;
        case XK_B:
            charKey = 'B';
            m_buttons[(key = PUNK_KEY_B)] = press;
            break;
        case XK_b:
            charKey = 'b';
            m_buttons[(key = PUNK_KEY_B)] = press;
            break;
        case XK_C:
            charKey = 'C';
            m_buttons[(key = PUNK_KEY_C)] = press;
            break;
        case XK_c:
            charKey = 'c';
            m_buttons[(key = PUNK_KEY_C)] = press;
            break;
        case XK_D:
            charKey = 'D';
            m_buttons[(key = PUNK_KEY_D)] = press;
            break;
        case XK_d:
            charKey = 'd';
            m_buttons[(key = PUNK_KEY_D)] = press;
            break;
        case XK_E:
            charKey = 'E';
            m_buttons[(key = PUNK_KEY_E)] = press;
            break;
        case XK_e:
            charKey = 'e';
            m_buttons[(key = PUNK_KEY_E)] = press;
            break;
        case XK_F:
            charKey = 'F';
            m_buttons[(key = PUNK_KEY_F)] = press;
            break;
        case XK_f:
            charKey = 'f';
            m_buttons[(key = PUNK_KEY_F)] = press;
            break;
        case XK_G:
            charKey = 'G';
            m_buttons[(key = PUNK_KEY_G)] = press;
            break;
        case XK_g:
            charKey = 'g';
            m_buttons[(key = PUNK_KEY_G)] = press;
            break;
        case XK_H:
            charKey = 'H';
            m_buttons[(key = PUNK_KEY_H)] = press;
            break;
        case XK_h:
            charKey = 'h';
            m_buttons[(key = PUNK_KEY_H)] = press;
            break;
        case XK_I:
            charKey = 'I';
            m_buttons[(key = PUNK_KEY_I)] = press;
            break;
        case XK_i:
            charKey = 'i';
            m_buttons[(key = PUNK_KEY_I)] = press;
            break;
        case XK_J:
            charKey = 'J';
            m_buttons[(key = PUNK_KEY_J)] = press;
            break;
        case XK_j:
            charKey = 'j';
            m_buttons[(key = PUNK_KEY_J)] = press;
            break;
        case XK_K:
            charKey = 'K';
            m_buttons[(key = PUNK_KEY_K)] = press;
            break;
        case XK_k:
            charKey = 'k';
            m_buttons[(key = PUNK_KEY_K)] = press;
            break;
        case XK_L:
            charKey = 'L';
            m_buttons[(key = PUNK_KEY_L)] = press;
            break;
        case XK_l:
            charKey = 'l';
            m_buttons[(key = PUNK_KEY_L)] = press;
            break;
        case XK_M:
            charKey = 'M';
            m_buttons[(key = PUNK_KEY_M)] = press;
            break;
        case XK_m:
            charKey = 'm';
            m_buttons[(key = PUNK_KEY_M)] = press;
            break;
        case XK_N:
            charKey = 'N';
            m_buttons[(key = PUNK_KEY_N)] = press;
            break;
        case XK_n:
            charKey = 'n';
            m_buttons[(key = PUNK_KEY_N)] = press;
            break;
        case XK_O:
            charKey = 'O';
            m_buttons[(key = PUNK_KEY_O)] = press;
            break;
        case XK_o:
            charKey = 'o';
            m_buttons[(key = PUNK_KEY_O)] = press;
            break;
        case XK_P:
            charKey = 'P';
            m_buttons[(key = PUNK_KEY_P)] = press;
            break;
        case XK_p:
            charKey = 'p';
            m_buttons[(key = PUNK_KEY_P)] = press;
            break;
        case XK_Q:
            charKey = 'Q';
            m_buttons[(key = PUNK_KEY_Q)] = press;
            break;
        case XK_q:
            charKey = 'q';
            m_buttons[(key = PUNK_KEY_Q)] = press;
            break;
        case XK_R:
            charKey = 'R';
            m_buttons[(key = PUNK_KEY_R)] = press;
            break;
        case XK_r:
            charKey = 'r';
            m_buttons[(key = PUNK_KEY_R)] = press;
            break;
        case XK_S:
            charKey = 'S';
            m_buttons[(key = PUNK_KEY_S)] = press;
            break;
        case XK_s:
            charKey = 's';
            m_buttons[(key = PUNK_KEY_S)] = press;
            break;
        case XK_T:
            charKey = 'T';
            m_buttons[(key = PUNK_KEY_T)] = press;
            break;
        case XK_t:
            charKey = 't';
            m_buttons[(key = PUNK_KEY_T)] = press;
            break;
        case XK_U:
            charKey = 'U';
            m_buttons[(key = PUNK_KEY_U)] = press;
            break;
        case XK_u:
            charKey = 'u';
            m_buttons[(key = PUNK_KEY_U)] = press;
            break;
        case XK_V:
            charKey = 'V';
            m_buttons[(key = PUNK_KEY_V)] = press;
            break;
        case XK_v:
            charKey = 'v';
            m_buttons[(key = PUNK_KEY_V)] = press;
            break;
        case XK_W:
            charKey = 'W';
            m_buttons[(key = PUNK_KEY_W)] = press;
            break;
        case XK_w:
            charKey = 'w';
            m_buttons[(key = PUNK_KEY_W)] = press;
            break;
        case XK_X:
            charKey = 'X';
            m_buttons[(key = PUNK_KEY_X)] = press;
            break;
        case XK_x:
            charKey = 'x';
            m_buttons[(key = PUNK_KEY_X)] = press;
            break;
        case XK_Y:
            charKey = 'Y';
            m_buttons[(key = PUNK_KEY_Y)] = press;
            break;
        case XK_y:
            charKey = 'y';
            m_buttons[(key = PUNK_KEY_Y)] = press;
            break;
        case XK_Z:
            charKey = 'Z';
            m_buttons[(key = PUNK_KEY_Z)] = press;
            break;
        case XK_z:
            charKey = 'z';
            m_buttons[(key = PUNK_KEY_Z)] = press;
            break;
        case XK_KP_0:
            m_buttons[(key = PUNK_KEY_NUM0)] = press;
            break;
        case XK_KP_1:
            m_buttons[(key = PUNK_KEY_NUM1)] = press;
            break;
        case XK_KP_2:
            m_buttons[(key = PUNK_KEY_NUM2)] = press;
            break;
        case XK_KP_3:
            m_buttons[(key = PUNK_KEY_NUM3)] = press;
            break;
        case XK_KP_4:
            m_buttons[(key = PUNK_KEY_NUM4)] = press;
            break;
        case XK_KP_5:
            m_buttons[(key = PUNK_KEY_NUM5)] = press;
            break;
        case XK_KP_6:
            m_buttons[(key = PUNK_KEY_NUM6)] = press;
            break;
        case XK_KP_7:
            m_buttons[(key = PUNK_KEY_NUM7)] = press;
            break;
        case XK_KP_8:
            m_buttons[(key = PUNK_KEY_NUM8)] = press;
            break;
        case XK_KP_9:
            m_buttons[(key = PUNK_KEY_NUM9)] = press;
            break;
        case XK_F1:
            m_buttons[(key = PUNK_KEY_F1)] = press;
            break;
        case XK_F2:
            m_buttons[(key = PUNK_KEY_F2)] = press;
            break;
        case XK_F3:
            m_buttons[(key = PUNK_KEY_F3)] = press;
            break;
        case XK_F4:
            m_buttons[(key = PUNK_KEY_F4)] = press;
            break;
        case XK_F5:
            m_buttons[(key = PUNK_KEY_F5)] = press;
            break;
        case XK_F6:
            m_buttons[(key = PUNK_KEY_F6)] = press;
            break;
        case XK_F7:
            m_buttons[(key = PUNK_KEY_F7)] = press;
            break;
        case XK_F8:
            m_buttons[(key = PUNK_KEY_F8)] = press;
            break;
        case XK_F9:
            m_buttons[(key = PUNK_KEY_F9)] = press;
            break;
        case XK_F10:
            m_buttons[(key = PUNK_KEY_F10)] = press;
            break;
        case XK_F11:
            m_buttons[(key = PUNK_KEY_F11)] = press;
            break;
        case XK_F12:
            m_buttons[(key = PUNK_KEY_F12)] = press;
            break;
        case XK_Shift_L:
            m_buttons[(key = PUNK_KEY_LEFT_SHIFT)] = press;
            break;
        case XK_Shift_R:
            m_buttons[(key = PUNK_KEY_RIGHT_SHIFT)] = press;
            break;
        case XK_Control_L:
            m_buttons[(key = PUNK_KEY_LEFT_CONTROL)] = press;
            break;
        case XK_Control_R:
            m_buttons[(key = PUNK_KEY_RIGHT_CONTROL)] = press;
            break;
        }
        return key;
    }

    void WindowX11::OnKeyPressRelease(XKeyEvent* event)
    {
        //  It is necessary to convert the keycode to a
        //  keysym before checking if it is an escape
        KeySym keysym = XLookupKeysym(event, 0);
        if (keysym != NoSymbol)//if (XLookupString(event,buffer,1, &keysym,NULL) == 1)
        {
            bool press = event->type == KeyPress;
            int charKey;
            int key = DecodeKey(keysym, charKey, press);
            KeyEvent e;
            e.key = key;
            e.transitionState = press;
            OnKeyEvent(e);
            if (charKey != 0 && press)
                OnCharEvent(e);
        }
    }

    void WindowX11::OnMousePressRelease(XEvent* event)
    {
        bool press = event->type == ButtonPress;

        MouseEvent mouse_event;
        mouse_event.x = event->xbutton.x;
        mouse_event.y = GetHeight() - event->xbutton.y;
        mouse_event.x_prev = x_prev;
        mouse_event.y_prev = y_prev;
        x_prev = mouse_event.x;
        y_prev = GetHeight() - event->xbutton.y;
        mouse_event.leftButton = m_left_button;
        mouse_event.middleButton = m_middle_button;
        mouse_event.rightButton = m_right_button;

        MouseWheelEvent wheel_event;
        wheel_event.x = event->xbutton.x;
        wheel_event.y = GetHeight() - event->xbutton.y;
        wheel_event.delta = 1;
        wheel_event.leftButton = m_left_button;
        wheel_event.middleButton = m_middle_button;
        wheel_event.rightButton = m_right_button;

        switch (event->xbutton.button)
        {
        case 1: //LEFT
        {
            mouse_event.leftButton = m_left_button = press;
            GetMouse()->SetButtonState(MouseButtons::LeftButton, press);
            OnMouseEvent(mouse_event);
            break;
        }
        case 2: //MIDDLE
        {
            mouse_event.middleButton = m_middle_button = press;
            GetMouse()->SetButtonState(MouseButtons::MiddleButton, press);
            OnMouseEvent(mouse_event);
            break;
        }
        case 3: //RIGHT
        {
            mouse_event.rightButton = m_right_button = press;
            GetMouse()->SetButtonState(MouseButtons::RightButton, press);
            OnMouseEvent(mouse_event);
            break;
        }
            break;
        case 4: //Wheel +
        {
            wheel_event.delta = 1;
            OnMouseWheelEvent(wheel_event);
            break;
        }
        case 5: //Wheel -
        {
            wheel_event.delta = -1;
            OnMouseWheelEvent(wheel_event);
            break;
        }
        }
    }

    int WindowX11::Loop()
    {        
        m_timer->Reset();

        while (!IsClosed())
        {
            int dt = m_timer->GetElapsedMiliseconds();
            if (!Update(dt))
                return 0;
            m_timer->Reset();
        }
        return 0;
    }

    int WindowX11::Update(int dt) {
        XEvent event;
        while (XPending(m_display))
        {
            XNextEvent(m_display, &event);
            switch (event.type)
            {
            case CreateNotify:
                OnWindowCreated();
                break;
            case ClientMessage:
                if (event.xclient.data.l[0] == (long)wmDeleteWindow) {
                    BreakMainLoop();
                    return 0;
                }
                break;
            case ConfigureNotify:
            {
                WindowResizeEvent e;
                e.width = event.xconfigure.width;
                e.height = event.xconfigure.height;
                OnResizeEvent(e);
                break;
            }
            case KeyPress:
            case KeyRelease:
            {
                OnKeyPressRelease((XKeyEvent*)&event);
                break;
            }
            case MotionNotify:
            {
                MouseEvent e;
                e.x_prev = x_prev;
                e.y_prev = y_prev;
                e.x = event.xmotion.x;
                e.y = GetHeight() - event.xmotion.y;
                x_prev = event.xmotion.x;
                y_prev = GetHeight() - event.xmotion.y;
                e.leftButton = m_left_button;
                e.middleButton = m_middle_button;
                e.rightButton = m_right_button;
                OnMouseMoveEvent(e);
                MouseMoveProc(e);
            }
                break;
            case ButtonPress:
            case ButtonRelease:
            {
                OnMousePressRelease(&event);
                break;
            }
            }
        }
        IdleEvent idle_event;
        idle_event.elapsed_time_s = dt / (double)1000;
        OnIdleEvent(idle_event);
        return 1;
    }

    void WindowX11::BreakMainLoop()
    {
        m_exit_main_loop = true;
    }

    bool WindowX11::IsClosed()
    {
        bool res = m_exit_main_loop;
        return res;
    }

    void WindowX11::SetTitle(const Core::String& text)
    {
        (void)text;
        // TODO: Implementation
    }

    const Core::String WindowX11::GetTitle() const
    {
        return Core::String();
    }


    void WindowX11::ShowCursor(bool value)
    {
        static Cursor invisible_cursor = None;
        if (invisible_cursor == None)
        {
            char cursorNoneBits[ 32 ];
            XColor dontCare;
            Pixmap cursorNonePixmap;
            memset( cursorNoneBits, 0, sizeof( cursorNoneBits ) );
            memset( &dontCare, 0, sizeof( dontCare ) );
            cursorNonePixmap = XCreateBitmapFromData( m_display,
                                                      m_window,
                                                      cursorNoneBits, 16, 16 );
            if( cursorNonePixmap != None ) {
                invisible_cursor = XCreatePixmapCursor(m_display,
                                                       cursorNonePixmap, cursorNonePixmap,
                                                       &dontCare, &dontCare, 0, 0 );
                XFreePixmap(m_display, cursorNonePixmap);
            }
        }
        if (value)
        {
            XUndefineCursor(m_display, m_window);
        }
        else
        {
            XDefineCursor(m_display, m_window, invisible_cursor);
        }
    }

    void WindowX11::Quite()
    {

    }

//    void WindowX11::DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
//    {
//        (void)x;
//        (void)y;
//        (void)r;
//        (void)g;
//        (void)b;
//        (void)a;
////        unsigned char rr = (unsigned char)std::max((int)r - int(255 - a), 0);
////        unsigned char gg = (unsigned char)std::max((int)g - int(255 - a), 0);
////        unsigned char bb = (unsigned char)std::max((int)b - int(255 - a), 0);
//    }

//    void WindowX11::DrawLine(int x1, int y1, int x2, int y2)
//    {
//        (void)x1;
//        (void)y1;
//        (void)x2;
//        (void)y2;
//    }

//    void WindowX11::SetWindow(::Window value)
//    {
//        if (m_window)
//            XDestroyWindow(m_display, m_window);
//        m_window = value;
//        XSetWMProtocols(m_display, m_window, &wmDeleteWindow, 1);
//    }


    void WindowX11::MouseMoveProc(const MouseEvent& e)
    {
        if (GetMouse()->IsLocked())
        {
            int w = GetWidth();
            int h = GetHeight();
            int w2 = w / 2;
            int h2 = h / 2;
            int w4 = w2 / 2;
            int h4 = h2 / 2;
            if (abs(e.x - w2) > w4 || abs(e.y - h2) > h4)
            {
                x_prev = w2;
                y_prev = h2;
                x = w2;
                y = h2;
                XWarpPointer(m_display, m_window, m_window, 0, 0, 0, 0, w2, h2);
            }
        }
    }

    void WindowX11::SetVisualInfo(XVisualInfo* visual) {
        m_visual = visual;
    }

    Window WindowX11::GetNativeHandle() {
        return m_window;
    }

    Display* WindowX11::GetDisplay() {
        if (!m_display) {
            m_display = XOpenDisplay(NULL);
            if (m_display == NULL)
                throw System::Error::SystemException("XWindow: can't open display");
        }
        return m_display;
    }

    void WindowX11::InternalCreate() {
        m_display = GetDisplay();

        int screen = DefaultScreen(m_display);
        memset(&m_swa, 0, sizeof(m_swa));
        m_swa.border_pixel      = WhitePixel(m_display,screen);
        m_swa.background_pixel = BlackPixel(m_display, screen);

        printf("Creating window\n");
        if (!m_visual) {
        m_window = XCreateWindow(m_display, DefaultRootWindow(m_display),
                                 m_window_description.m_x, m_window_description.m_y, m_window_description.m_width, m_window_description.m_height,
                                 0, DefaultDepth(m_display, screen),
                                 CopyFromParent, CopyFromParent, CWBackPixel|CWBorderPixel, &m_swa);
        }
        else {
            printf( "Creating colormap\n" );
            Colormap colorMap;
            XSetWindowAttributes swa;
            swa.colormap = colorMap = XCreateColormap( m_display,
                                                       RootWindow( m_display, m_visual->screen ),
                                                       m_visual->visual, AllocNone );
            swa.background_pixmap = None ;
            swa.border_pixel      = 0;
            swa.event_mask        = KeyPressMask | PointerMotionMask | StructureNotifyMask
                    | ButtonPressMask;

            printf( "Creating window\n" );
            m_window = XCreateWindow( m_display,
                                         RootWindow( m_display, m_visual->screen ),
                                         m_window_description.m_x, m_window_description.m_y, m_window_description.m_width, m_window_description.m_height, 0, m_visual->depth, InputOutput,
                                         m_visual->visual,
                                         CWBorderPixel|CWColormap|CWEventMask, &swa );
        }

        XStoreName(m_display, m_window, "PunkEngine");
        XSetIconName(m_display, m_window, "PunkEngine");
        XSetCommand(m_display, m_window, 0, 0);
        XFlush(m_display);

        //        XSetStandardProperties(m_display, m_window, "PunkEngine", "Icon", None, 0, 0, 0);
        XMapWindow(m_display, m_window);
        int eventMask = ButtonPressMask
                |ButtonReleaseMask
                |KeyPressMask
                |ExposureMask
                |StructureNotifyMask
                |PointerMotionMask;

        XSelectInput(m_display, m_window, eventMask); // override prev

        wmDeleteWindow = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &wmDeleteWindow, 1);
    }

    void WindowX11::InternalDestroy() {
        XDestroyWindow(m_display, m_window);
        XSetCloseDownMode(m_display, DestroyAll );
        XCloseDisplay(m_display);
    }

    PUNK_REGISTER_CREATOR(IID_IWindow, (Core::CreateInstance<WindowX11, IWindow>));
}
PUNK_ENGINE_END
#endif  //  __gnu_linux
