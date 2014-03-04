#include <string/module.h>
#include <system/logger/module.h>
#include <graphics/error/module.h>
#include <graphics/opengl/module.h>
#include "canvas.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    Canvas::Canvas(const CanvasDescription& desc)
        : System::WindowWin(desc)
        , m_canvas_description(desc)
        , m_logger(System::GetDefaultLogger())
    {}

    void Canvas::InternalDestroy()
    {}

    void Canvas::OnResize(const System::WindowResizeEvent &)
    {}

    void Canvas::SetFullscreen(bool value) {
    }

    void Canvas::InternalCreate()
    {
        m_logger->Info(L"Initializing OpenGL...");

        HDC deviceContext = ::GetDC((HWND)*this);

        int pixelFormat;
        static PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(pfd),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
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
            throw Error::CreateOpenGLContextError(L"Can't create temporary opengl context");

        if (!wglMakeCurrent(deviceContext, tempContext))
            throw Error::OpenGLContextMakeCurrentError(L"Can't set created context to be current");

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

        //		int forward = 0;
        int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                            WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
                            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
                            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
                           };

        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)gl::GetGPUProcAddress("wglCreateContextAttribsARB");

        if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
            throw Error::OpenGLCreateContextError(L"Can't create opengl 3.x context");

        if (!wglMakeCurrent(deviceContext, m_opengl_context))
            throw Error::OpenGLContextMakeCurrentError(L"Can't set opengl 3.x context to be current");

        wglDeleteContext(tempContext);

        gl::InitExtensions();

        GLint t;
        m_logger->Info(Core::String("\tRenderer: {0} ").arg((const char*)gl::glGetString(GL_RENDERER)));
        m_logger->Info(Core::String("\tVendor: {0} ").arg((const char*)gl::glGetString(GL_VENDOR)));
        m_logger->Info(Core::String("\tVersion: {0}").arg((const char*)gl::glGetString(GL_VERSION)));
        m_logger->Info(Core::String("\tGLSL version: {0}").arg((const char*)gl::glGetString(GL_SHADING_LANGUAGE_VERSION)));
        gl::glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &t);
        m_logger->Info(Core::String("\tMax vertex attribs: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &t);
        m_logger->Info(Core::String("\tMax vertex uniform components: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_VARYING_FLOATS, &t);
        m_logger->Info(Core::String("\tMax varying floats: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax 3D texture size: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_CLIP_DISTANCES, &t);
        m_logger->Info(Core::String(L"\tMax clip distances: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &t);
        m_logger->Info(Core::String(L"\tMax combined texture image units: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax cube map texture size: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_DRAW_BUFFERS, &t);
        m_logger->Info(Core::String(L"\tMax draw buffers: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &t);
        m_logger->Info(Core::String(L"\tMax elements indices: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &t);
        m_logger->Info(Core::String(L"\tMax elements vertices: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);
        m_logger->Info(Core::String(L"\tMax texture image units in FS: {0}").arg(t));
        gl::glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &t);
        m_logger->Info(Core::String(L"\tMax render buffer size: {0}").arg(t));


        gl::wglSwapIntervalEXT(0);

        const unsigned char* sv = gl::glGetString(GL_SHADING_LANGUAGE_VERSION);
        m_shader_version = ((int)(sv[0]-'0'))*100;
        m_shader_version += ((int)(sv[2]-'0'))*10;
        m_shader_version += ((int)(sv[3]-'0'));

        sv = gl::glGetString(GL_VERSION);
        m_opengl_version = ((int)(sv[0]-'0'))*100;
        m_opengl_version += ((int)(sv[2]-'0'))*10;
        m_opengl_version += ((int)(sv[3]-'0'));

        int profile;
        gl::glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCore profile selected");
        if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCompatible profile selected");

        SubscribeResizeEvent(new Core::Action<Canvas, const System::WindowResizeEvent&>(this, &Canvas::OnResize));
        //m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &VideoDriverImpl::OnKeyDown));
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
