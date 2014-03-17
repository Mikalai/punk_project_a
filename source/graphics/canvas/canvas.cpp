#include <string/module.h>
#include <system/logger/module.h>
#include <system/events/module.h>
#include <system/input/module.h>
#include <graphics/error/module.h>
#include <graphics/opengl/module.h>
#include <graphics/video_driver/module.h>
#include "canvas.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    Canvas::Canvas(const CanvasDescription& desc)
        : System::WindowWin(desc)
        , m_canvas_description(desc)
        , m_logger(System::GetDefaultLogger())
    {}

    void Canvas::InternalDestroy() {
        if (m_canvas_description.fullscreen)
            SetFullscreen(false);
        ChangeDisplaySettings(NULL, 0);
        wglMakeCurrent(::GetDC(*this), NULL);
        wglDeleteContext(m_opengl_context);
        Constructor::DestroyVideoDriver(m_video_driver);
        WindowWin::InternalDestroy();
    }

    void Canvas::OnResize(const System::WindowResizeEvent &)
    {
    }

    void Canvas::SetFullscreen(bool flag) {
        m_canvas_description.fullscreen = flag;
        if (flag)
        {
            SetWindowLong(*this, GWL_STYLE, WS_POPUP);
            SetWindowLong(*this, GWL_EXSTYLE, WS_EX_APPWINDOW);

            m_logger->Info(L"Enter fullscreen mode...");
            DEVMODE mode;
            ZeroMemory(&mode, sizeof(mode));
            mode.dmSize = sizeof(mode);
            mode.dmPelsWidth = m_canvas_description.m_width;
            mode.dmPelsHeight = m_canvas_description.m_height;
            mode.dmBitsPerPel = m_canvas_description.bits_per_pixel;
            mode.dmDisplayFrequency = m_canvas_description.refresh_frequency;
            mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

            SetWindowPos(*this, 0, 0, 0, m_canvas_description.m_width, m_canvas_description.m_height, SWP_SHOWWINDOW);

            LONG code;
            if ((code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN)) != DISP_CHANGE_SUCCESSFUL)
                throw Error::CantSetFullscreenError(L"Can't change display settings");
        }
        else
        {
            SetWindowLong(*this, GWL_STYLE, WS_OVERLAPPEDWINDOW);
            SetWindowLong(*this, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

            m_logger->Info(L"Enter window mode...");
            SetPosition(m_canvas_description.m_x, m_canvas_description.m_y);
            SetSize(m_canvas_description.m_width, m_canvas_description.m_height);
        }

        ShowWindow(*this, SW_SHOW);
        SetFocus(*this);
    }

    void Canvas::SwapBuffers()
    {
#ifdef _WIN32
        if (!::SwapBuffers(::GetDC(*this)))
            m_logger->Error(L"Swap buffer failed");
#elif defined __gnu_linux__
        glXSwapBuffers(m_desc.window->GetDisplay(), m_desc.window->GetWindow());
#endif
    }

    void Canvas::InternalCreate()
    {
        WindowWin::InternalCreate();
        m_logger->Info(L"Initializing OpenGL...");

        HDC deviceContext = ::GetDC((HWND)*this);

        int pixelFormat;
        static PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(pfd),
            1,
            PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL |
            PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            (BYTE)m_canvas_description.bits_per_pixel,
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            16,
            0,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        if (!(pixelFormat = ChoosePixelFormat(deviceContext, &pfd)))
            throw Error::ChoosePixelFormatError(L"Can't choose pixel format");

        if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
            throw Error::SetPixelFormatError(L"Can't set pixel format");

        HGLRC tempContext;
        if ((tempContext = wglCreateContext(deviceContext)) == NULL)
            throw OpenGL::OpenGLCreateContextError(L"Can't create temporary opengl context");

        if (!wglMakeCurrent(deviceContext, tempContext))
            throw OpenGL::OpenGLContextMakeCurrentError(L"Can't set created context to be current");

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

        //		int forward = 0;
        int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                            WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
                            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
                            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
                           };

        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)OpenGL::GetGraphicsProcAddress("wglCreateContextAttribsARB");

        if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
            throw OpenGL::OpenGLCreateContextError(L"Can't create opengl 3.x context");

        if (!wglMakeCurrent(deviceContext, m_opengl_context))
            throw OpenGL::OpenGLContextMakeCurrentError(L"Can't set opengl 3.x context to be current");

        wglDeleteContext(tempContext);

        OpenGL::InitExtensions();

        GLint t;
        m_logger->Info(Core::String("\tRenderer: {0} ").arg((const char*)OpenGL::glGetString(GL_RENDERER)));
        m_logger->Info(Core::String("\tVendor: {0} ").arg((const char*)OpenGL::glGetString(GL_VENDOR)));
        m_logger->Info(Core::String("\tVersion: {0}").arg((const char*)OpenGL::glGetString(GL_VERSION)));
        m_logger->Info(Core::String("\tGLSL version: {0}").arg((const char*)OpenGL::glGetString(GL_SHADING_LANGUAGE_VERSION)));
        OpenGL::glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
        m_logger->Info(Core::String("\tMax vertex attribs: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
        m_logger->Info(Core::String("\tMax vertex uniform components: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
        m_logger->Info(Core::String("\tMax varying floats: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax 3D texture size: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_CLIP_DISTANCES, &t);
        m_logger->Info(Core::String(L"\tMax clip distances: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &t);
        m_logger->Info(Core::String(L"\tMax combined texture image units: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax cube map texture size: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_DRAW_BUFFERS, &t);
        m_logger->Info(Core::String(L"\tMax draw buffers: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &t);
        m_logger->Info(Core::String(L"\tMax elements indices: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &t);
        m_logger->Info(Core::String(L"\tMax elements vertices: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);
        m_logger->Info(Core::String(L"\tMax texture image units in FS: {0}").arg(t));
        OpenGL::glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax render buffer size: {0}").arg(t));


        OpenGL::wglSwapIntervalEXT(0);

        const unsigned char* sv = OpenGL::glGetString(GL_SHADING_LANGUAGE_VERSION);
        m_shader_version = ((int)(sv[0]-'0'))*100;
        m_shader_version += ((int)(sv[2]-'0'))*10;
        m_shader_version += ((int)(sv[3]-'0'));

        sv = OpenGL::glGetString(GL_VERSION);
        m_opengl_version = ((int)(sv[0]-'0'))*100;
        m_opengl_version += ((int)(sv[2]-'0'))*10;
        m_opengl_version += ((int)(sv[3]-'0'));

        int profile;
        OpenGL::glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCore profile selected");
        if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCompatible profile selected");

        SubscribeResizeEvent(new Core::Action<Canvas, const System::WindowResizeEvent&>(this, &Canvas::OnResize));

        SetFullscreen(m_canvas_description.fullscreen);

        m_video_driver = Constructor::CreateVideoDriver(this);
        OpenGL::glViewport(0, m_canvas_description.m_width, 0, m_canvas_description.m_height);
        OpenGL::glClearColor(0, 0, 1, 1);
        OpenGL::glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        SwapBuffers();
        //m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &VideoDriverImpl::OnKeyDown));
    }

    void Canvas::OnKeyDown(const System::KeyEvent& e) {
        if (e.key == System::PUNK_KEY_ENTER) {
            if (System::GetKeyboard()->GetKeyState(System::PUNK_KEY_ALT))
                SetFullscreen(!m_canvas_description.fullscreen);
        }
    }


    Canvas::~Canvas() {}

    const CanvasDescription& Canvas::GetDescription() {
        return m_canvas_description;
    }

    IVideoDriver* Canvas::GetVideoDriver() {
        return m_video_driver;
    }

    System::IWindow* Canvas::GetWindow() {
        return this;
    }

    extern "C" PUNK_ENGINE_API ICanvas* CreateCanvas(const CanvasDescription& desc) {
        return new Canvas(desc);
    }

    extern "C" PUNK_ENGINE_API void DestroyCanvas(ICanvas* value) {
        Canvas* canvas = dynamic_cast<Canvas*>(value);
        delete canvas;
    }
}
PUNK_ENGINE_END
