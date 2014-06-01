#include <core/factory.h>
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

    Canvas::Canvas()		
		: m_window{ Core::CreateInstance<System::IWindow>(System::IID_IWindow), Core::DestroyObject }
        , m_logger(System::GetDefaultLogger())
    {}

	void Canvas::Initialize(const CanvasDescription& desc) {
		m_canvas_description = desc;		
	}

    void Canvas::InternalDestroy() {
        if (m_canvas_description.fullscreen)
			SetFullscreen(false);
        ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(::GetDC(GetNativeHandle()), NULL);
        wglDeleteContext(m_opengl_context);        
        m_window->InternalDestroy();
    }

    void Canvas::OnResize(const System::WindowResizeEvent &)
    {
    }

	void Canvas::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (void*)(Core::IObject*)(ICanvas*)this;
			AddRef();
			return;
		}
		else if (type == IID_ICanvas) {
			*object = (void*)(ICanvas*)this;
			AddRef();
			return;
		}
		else if (type == System::IID_IWindow) {
			*object = (void*)(System::IWindow*)this;
			AddRef();
			return;
		}
	}

	std::uint32_t Canvas::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t Canvas::Release() {
		if (!(m_ref_count.fetch_sub(1)-1)) {
			delete this; \
		}
		return m_ref_count;
	}


    void Canvas::SetFullscreen(bool flag) {
        m_canvas_description.fullscreen = flag;
        if (flag)
        {
            SetWindowLong(GetNativeHandle(), GWL_STYLE, WS_POPUP);
            SetWindowLong(GetNativeHandle(), GWL_EXSTYLE, WS_EX_APPWINDOW);

            m_logger->Info(L"Enter fullscreen mode...");
            DEVMODE mode;
            ZeroMemory(&mode, sizeof(mode));
            mode.dmSize = sizeof(mode);
            mode.dmPelsWidth = m_canvas_description.m_width;
            mode.dmPelsHeight = m_canvas_description.m_height;
            mode.dmBitsPerPel = m_canvas_description.bits_per_pixel;
            mode.dmDisplayFrequency = m_canvas_description.refresh_frequency;
            mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

			SetWindowPos(GetNativeHandle(), 0, 0, 0, m_canvas_description.m_width, m_canvas_description.m_height, SWP_SHOWWINDOW);

            LONG code;
            if ((code = ChangeDisplaySettings(&mode, CDS_FULLSCREEN)) != DISP_CHANGE_SUCCESSFUL)
                throw Error::CantSetFullscreenError(L"Can't change display settings");
        }
        else
        {
            SetWindowLong(GetNativeHandle(), GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowLong(GetNativeHandle(), GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

            m_logger->Info(L"Enter window mode...");
            SetPosition(m_canvas_description.m_x, m_canvas_description.m_y);
            SetSize(m_canvas_description.m_width, m_canvas_description.m_height);
        }

		ShowWindow(GetNativeHandle(), SW_SHOW);
		SetFocus(GetNativeHandle());
    }

    void Canvas::SwapBuffers()
    {
#ifdef _WIN32
		if (!::SwapBuffers(::GetDC(GetNativeHandle())))
            m_logger->Error(L"Swap buffer failed");
#elif defined __gnu_linux__
        glXSwapBuffers(m_desc.window->GetDisplay(), m_desc.window->GetWindow());
#endif
    }

    void Canvas::InternalCreate()
    {
        m_window->InternalCreate();
        m_logger->Info(L"Initializing OpenGL...");

		HDC deviceContext = ::GetDC(GetNativeHandle());

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

        //		int forward ;
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

		Core::GetFactory()->CreateInstance(IID_IVideoDriver, (void**)&m_video_driver);
		m_video_driver->Initialize(this);

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
        return m_video_driver.get();
    }

    System::IWindow* Canvas::GetWindow() {
        return this;
    }

	//	IWindow

	void Canvas::Initialize(const System::WindowDescription& desc) {
		m_window->Initialize(desc);
	}

	int Canvas::GetDesktopWidth() const {
		return m_window->GetDesktopWidth();
	}
	
	int Canvas::GetDesktopHeight() const {
		return m_window->GetDesktopHeight();
	}

	int Canvas::GetDesktopBitsPerPixel() const {
		return m_window->GetDesktopBitsPerPixel();
	}

	int Canvas::GetDesktopRefreshRate() const {
		return m_window->GetDesktopRefreshRate();
	}

	int Canvas::GetWidth() const {
		return m_window->GetWidth();
	}

	int Canvas::GetHeight() const {
		return m_window->GetHeight();
	}

	int Canvas::GetX() const {
		return m_window->GetX();
	}

	int Canvas::GetY() const {
		return m_window->GetY();
	}

	void Canvas::SetSize(int width, int height) {
		m_window->SetSize(width, height);
	}

	void Canvas::SetPosition(int x, int y) {
		m_window->SetPosition(x, y);
	}

	int Canvas::Update(int dt) {
		return m_window->Update(dt);
	}

	int Canvas::Loop() {
		return m_window->Loop();
	}

	void Canvas::BreakMainLoop() {
		m_window->BreakMainLoop();
	}

	void Canvas::SetTitle(const Core::String& text) {
		m_window->SetTitle(text);
	}

	const Core::String Canvas::GetTitle() const {
		return m_window->GetTitle();
	}

	void Canvas::Quite() {
		m_window->Quite();
	}

	void Canvas::ShowCursor(bool value) {
		m_window->ShowCursor(value);
	}

	void Canvas::SubscribeResizeEvent(System::ResizeEventDelegate value) {
		m_window->SubscribeResizeEvent(value);
	}

	void Canvas::UnsubscribeResizeEvent(System::ResizeEventDelegate value) {
		m_window->UnsubscribeResizeEvent(value);
	}

	void Canvas::SubscribeKeyEvent(System::KeyEventDelegate value) {
		m_window->SubscribeKeyEvent(value);
	}

	void Canvas::UnsubscribeKeyEvent(System::KeyEventDelegate value) {
		m_window->UnsubscribeKeyEvent(value);
	}

	void Canvas::SubscribeCharEvent(System::CharEventDelegate value) {
		m_window->SubscribeCharEvent(value);
	}

	void Canvas::UnsubscribeCharEvent(System::CharEventDelegate value) {
		m_window->UnsubscribeCharEvent(value);
	}

	void Canvas::SubscribeMouseEvent(System::MouseEventDelegate value) {
		m_window->SubscribeMouseEvent(value);
	}

	void Canvas::UnsubscribeMouseEvent(System::MouseEventDelegate value) {
		m_window->UnsubscribeMouseEvent(value);
	}

	void Canvas::SubscribeMouseEvent(void(*Delegate)(const System::MouseEvent&))  {
		m_window->SubscribeMouseEvent(Delegate);
	}

	void Canvas::UnsubscribeMouseEvent(void(*Delegate)(const System::MouseEvent&)) {
		m_window->UnsubscribeMouseEvent(Delegate);
	}

	void Canvas::SubscribeMouseMoveEvent(System::MouseMoveEventDelegate value) {
		m_window->SubscribeMouseMoveEvent(value);
	}

	void Canvas::UnsubscribeMouseMoveEvent(System::MouseMoveEventDelegate value) {
		m_window->UnsubscribeMouseMoveEvent(value);
	}

	void Canvas::SubscribeMouseHooverEvent(System::MouseHooverEventDelegate value) {
		m_window->SubscribeMouseHooverEvent(value);
	}

	void Canvas::UnsubscribeMouseHooverEvent(System::MouseHooverEventDelegate value) {
		m_window->UnsubscribeMouseHooverEvent(value);
	}

	void Canvas::SubscribeMouseWheelEvent(System::MouseWheelEventDelegate value) {
		m_window->SubscribeMouseWheelEvent(value);
	}

	void Canvas::UnsubscribeMouseWheelEvent(System::MouseWheelEventDelegate value) {
		m_window->UnsubscribeMouseWheelEvent(value);
	}

	void Canvas::SubscribeWindowCreatedEvent(System::WindowCreatedDelegate value) {
		m_window->SubscribeWindowCreatedEvent(value);
	}

	void Canvas::UnsubscribeWindowCreatedEvent(System::WindowCreatedDelegate value) {
		m_window->UnsubscribeWindowCreatedEvent(value);
	}

	void Canvas::SubscribeWindowDestroyEvent(System::WindowDestroyDelegate value) {
		m_window->SubscribeWindowDestroyEvent(value);
	}

	void Canvas::SubscribeWindowDestroyEvent(void(*Delegate)()) {
		m_window->SubscribeWindowDestroyEvent(Delegate);
	}

	void Canvas::UnsubscribeWindowDestroyEvent(System::WindowDestroyDelegate value) {
		m_window->UnsubscribeWindowDestroyEvent(value);
	}

	void Canvas::UnsubscribeWindowDestroyEvent(void(*Delegate)()) {
		m_window->UnsubscribeWindowDestroyEvent(Delegate);
	}

	void Canvas::SubscribeIdleEvent(System::IdleEventDelegate value) {
		m_window->SubscribeIdleEvent(value);
	}

	void Canvas::UnsubscribeIdleEvent(System::IdleEventDelegate value) {
		m_window->UnsubscribeIdleEvent(value);
	}

	void Canvas::SubscribeIdleEvent(void(*Delegate)(const System::IdleEvent&)) {
		m_window->SubscribeIdleEvent(Delegate);
	}

	void Canvas::UnsubscribeIdleEvent(void(*Delegate)(const System::IdleEvent&)) {
		m_window->UnsubscribeIdleEvent(Delegate);
	}

	void Canvas::Open() {
		InternalCreate();		
	}

	void Canvas::Close() {
		InternalDestroy();
	}

#ifdef _WIN32
	HWND Canvas::GetNativeHandle() {
		return m_window->GetNativeHandle();
	}

#endif	//	 _WIN32

	PUNK_REGISTER_CREATOR(IID_ICanvas, Core::CreateInstance<Canvas>);
}
PUNK_ENGINE_END
