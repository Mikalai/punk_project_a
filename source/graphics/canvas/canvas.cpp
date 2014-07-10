#include <system/factory/module.h>
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
        : m_logger(System::GetDefaultLogger())
        , m_window{ System::CreateInstance<System::IWindow>(System::IID_IWindow), Core::DestroyObject }
    {
#ifdef WIN32        
#elif defined __linux__
#endif
    }

	void Canvas::Initialize(const CanvasDescription& desc) {
		m_canvas_description = desc;		
	}

    void Canvas::InternalDestroy() {
        if (m_canvas_description.fullscreen)
			SetFullscreen(false);
#ifdef WIN32
        ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(::GetDC(GetNativeHandle()), NULL);
        wglDeleteContext(m_opengl_context);        
        m_window->InternalDestroy();
#elif defined __linux__
#endif
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
        auto v = m_ref_count.fetch_sub(1)-1;
        if (!v) {
            delete this;
		}
        return v;
	}


    void Canvas::SetFullscreen(bool flag) {
        m_canvas_description.fullscreen = flag;
#ifdef WIN32
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
#elif defined __linux__
#endif
    }

    void Canvas::SwapBuffers()
    {
#ifdef _WIN32
		if (!::SwapBuffers(::GetDC(GetNativeHandle())))
            m_logger->Error(L"Swap buffer failed");
#elif defined __gnu_linux__
        OpenGL::glXSwapBuffers(m_window->GetDisplay(), m_window->GetNativeHandle());
#endif
    }

    void Canvas::InternalCreate()
    {
#ifdef WIN32
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
            throw OpenGL::Error::OpenGLCreateContextError(L"Can't create temporary opengl context");

        if (!wglMakeCurrent(deviceContext, tempContext))
			throw OpenGL::Error::OpenGLContextMakeCurrentError(L"Can't set created context to be current");

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

        //		int forward ;
        int attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                            WGL_CONTEXT_MINOR_VERSION_ARB, 3, 0,
                            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
                            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB
                           };

        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)OpenGL::GetGraphicsProcAddress("wglCreateContextAttribsARB");

        if (!(m_opengl_context = wglCreateContextAttribsARB(deviceContext, 0, attributes)))
            throw OpenGL::Error::OpenGLCreateContextError(L"Can't create opengl 3.x context");

        if (!wglMakeCurrent(deviceContext, m_opengl_context))
            throw OpenGL::Error::OpenGLContextMakeCurrentError(L"Can't set opengl 3.x context to be current");

        wglDeleteContext(tempContext);

        //m_desc.event_manager->SubscribeHandler(System::EVENT_KEY_DOWN, System::EventHandler(this, &VideoDriverImpl::OnKeyDown));
#elif defined __linux__        

        OpenGL::InitializeOpenGLWindowSystem();

        auto display = m_window->GetDisplay();
        static int visual_attribs[] =
        {
            GLX_X_RENDERABLE,       true,
            GLX_DRAWABLE_TYPE,      GLX_WINDOW_BIT,
            //        GLX_RENDER_TYPE,        GLX_RGBA_BIT,
            //        GLX_X_VISUAL_TYPE,      GLX_TRUE_COLOR,
            //        GLX_RED_SIZE,           8,
            //        GLX_GREEN_SIZE,         8,
            //        GLX_BLUE_SIZE,          8,
            //        GLX_ALPHA_SIZE,         8,
            //        GLX_DEPTH_SIZE,         24,
            //        GLX_STENCIL_SIZE,       8,
            //        GLX_DOUBLEBUFFER,       true,
            None
        };

        int glx_major = 0, glx_minor = 0;

        if (!OpenGL::glXQueryVersion(display, &glx_minor, &glx_major) ||
                (( glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
        {
            m_logger->Info(Core::String("GLX VERSION: {0}.{1}").arg(glx_major).arg(glx_minor));
            throw System::Error::SystemException("Bad glx version");
        }
        else {
            m_logger->Info(Core::String("GLX VERSION: {0}.{1}").arg(glx_major).arg(glx_minor));
        }

        int count;
        GLXFBConfig* confs = OpenGL::glXGetFBConfigs(display, DefaultScreen(display), &count);
        for (int i = 0; i != count; ++i)
        {
            int value;
            //m_logger->Info(Core::String("Config {0}/{1}").arg(i+1).arg(count));
            int params[] = {GLX_DRAWABLE_TYPE, GLX_USE_GL, GLX_BUFFER_SIZE};
            Core::String strs[] = {Core::String("GLX_DRAWABLE_TYPE: {0}"), Core::String("GLX_USE_GL: {0}"), Core::String("GLX_BUFFER_SIZE: {0}")};

            for (int j = 0; j < sizeof(params)/sizeof(params[0]); ++j) {
                OpenGL::glXGetFBConfigAttrib(display, confs[i], params[j], &value);
                //m_logger->Info(strs[j].arg(value));
            }

//            glXGetFBConfigAttrib(display, confs[i], GLX_LEVEL, &value);
//            m_logger->Info(Core::String("GLX_LEVEL: {0}").arg(value));

//            glXGetFBConfigAttrib(display, confs[i], GLX_RGBA, &value);
//            m_logger->Info(Core::String("GLX_RGBA: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_DOUBLEBUFFER, &value);
//            m_logger->Info(Core::String("GLX_DOUBLEBUFFER: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_STEREO, &value);
//            m_logger->Info(Core::String("GLX_STEREO: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_AUX_BUFFERS, &value);
//            m_logger->Info(Core::String("GLX_AUX_BUFFERS: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_RED_SIZE, &value);
//            m_logger->Info(Core::String("GLX_RED_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_BLUE_SIZE, &value);
//            m_logger->Info(Core::String("GLX_BLUE_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_ALPHA_SIZE, &value);
//            m_logger->Info(Core::String("GLX_ALPHA_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_DEPTH_SIZE, &value);
//            m_logger->Info(Core::String("GLX_DEPTH_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_STENCIL_SIZE, &value);
//            m_logger->Info(Core::String("GLX_STENCIL_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_RED_SIZE, &value);
//            m_logger->Info(Core::String("GLX_ACCUM_RED_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_GREEN_SIZE, &value);
//            m_logger->Info(Core::String("GLX_ACCUM_GREEN_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_BLUE_SIZE, &value);
//            m_logger->Info(Core::String("GLX_ACCUM_BLUE_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_ALPHA_SIZE, &value);
//            m_logger->Info(Core::String("GLX_ACCUM_ALPHA_SIZE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_CONFIG_CAVEAT, &value);
//            m_logger->Info(Core::String("GLX_CONFIG_CAVEAT: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_X_VISUAL_TYPE, &value);
//            m_logger->Info(Core::String("GLX_X_VISUAL_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_TYPE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_INDEX_VALUE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_INDEX_VALUE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_RED_VALUE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_RED_VALUE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_GREEN_VALUE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_GREEN_VALUE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_BLUE_VALUE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_BLUE_VALUE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_ALPHA_VALUE, &value);
//            m_logger->Info(Core::String("GLX_TRANSPARENT_ALPHA_VALUE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_SLOW_CONFIG, &value);
//            m_logger->Info(Core::String("GLX_SLOW_CONFIG: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRUE_COLOR, &value);
//            m_logger->Info(Core::String("GLX_TRUE_COLOR: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_DIRECT_COLOR, &value);
//            m_logger->Info(Core::String("GLX_DIRECT_COLOR: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_PSEUDO_COLOR, &value);
//            m_logger->Info(Core::String("GLX_PSEUDO_COLOR: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_STATIC_COLOR, &value);
//            m_logger->Info(Core::String("GLX_STATIC_COLOR: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_GRAY_SCALE, &value);
//            m_logger->Info(Core::String("GLX_GRAY_SCALE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_STATIC_GRAY, &value);
//            out_message() << "GLX_STATIC_GRAY: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_RGB, &value);
//            out_message() << "GLX_TRANSPARENT_RGB: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_INDEX, &value);
//            out_message() << "GLX_TRANSPARENT_INDEX: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_VISUAL_ID, &value);
//            out_message() << "GLX_VISUAL_ID: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_NON_CONFORMANT_CONFIG, &value);
//            out_message() << "GLX_NON_CONFORMANT_CONFIG: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_DRAWABLE_TYPE, &value);
//            out_message() << "GLX_DRAWABLE_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_RENDER_TYPE, &value);
//            out_message() << "GLX_RENDER_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_X_RENDERABLE, &value);
//            out_message() << "GLX_X_RENDERABLE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_FBCONFIG_ID, &value);
//            out_message() << "GLX_FBCONFIG_ID: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_RGBA_TYPE, &value);
//            out_message() << "GLX_RGBA_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_COLOR_INDEX_TYPE, &value);
//            out_message() << "GLX_COLOR_INDEX_TYPE: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_WIDTH, &value);
//            out_message() << "GLX_MAX_PBUFFER_WIDTH: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_HEIGHT, &value);
//            out_message() << "GLX_MAX_PBUFFER_HEIGHT: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_PIXELS, &value);
//            out_message() << "GLX_MAX_PBUFFER_PIXELS: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_PRESERVED_CONTENTS, &value);
//            out_message() << "GLX_PRESERVED_CONTENTS: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_LARGEST_PBUFFER, &value);
//            out_message() << "GLX_LARGEST_PBUFFER: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_WIDTH, &value);
//            out_message() << "GLX_WIDTH: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_HEIGHT, &value);
//            out_message() << "GLX_HEIGHT: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_EVENT_MASK, &value);
//            out_message() << "GLX_EVENT_MASK: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_SAVED, &value);
//            out_message() << "GLX_SAVED: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_WINDOW, &value);
//            out_message() << "GLX_WINDOW: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER, &value);
//            out_message() << "GLX_PBUFFER: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER_HEIGHT, &value);
//            out_message() << "GLX_PBUFFER_HEIGHT: " << value << std::endl;

//            glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER_WIDTH, &value);
//            out_message() << "GLX_PBUFFER_WIDTH: " << value << std::endl;
        }

        int fbcount;
        GLXFBConfig* fbc = OpenGL::glXChooseFBConfig(display, DefaultScreen(display),
                                             visual_attribs, &fbcount);

        fbc = &confs[2];
        fbcount = 1;

        if (!fbc)
            throw System::Error::SystemException("unable to create framebuffer");

        printf("found %d matching framebuffers", fbcount);

        // Pick the FB config/visual with the most samples per pixel
        printf( "Getting XVisualInfos\n" );
        int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

        for (int i = 0; i < fbcount; i++ )
        {
            XVisualInfo *vi = OpenGL::glXGetVisualFromFBConfig(display, fbc[i] );
            if ( vi )
            {
                int samp_buf, samples;
                OpenGL::glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
                OpenGL::glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

                printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
                        " SAMPLES = %d\n",
                        i, vi -> visualid, samp_buf, samples );

                if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
                    best_fbc = i, best_num_samp = samples;
                if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                    worst_fbc = i, worst_num_samp = samples;
            }
            XFree( vi );
        }

        GLXFBConfig bestFbc = fbc[ best_fbc ];

        // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
        XFree( confs );

        // Get a visual
        XVisualInfo *vi = OpenGL::glXGetVisualFromFBConfig(display, bestFbc );
        printf( "Chosen visual ID = 0x%x\n", vi->visualid );

        m_window->SetVisualInfo(vi);
        m_window->InternalCreate();
        m_window->SetVisualInfo(nullptr);

        // Done with the visual info data
        XFree( vi );        

        // Get the default screen's GLX extension list
        const char *glxExts = OpenGL::glXQueryExtensionsString( display, DefaultScreen( display ) );

        printf("Extesion string is %s\n", glxExts);
        // NOTE: It is not necessary to create or make current to a context before
        // calling glXGetProcAddressARB
        printf("glXGetProcAddress %p\n", OpenGL::glXGetProcAddress);
        printf("glxCreateContextAttribsARB address is %p\n", OpenGL::glXCreateContextAttribsARB);

        printf("glxCreateContextAttribsARB address is %p\n", OpenGL::glXCreateContextAttribsARB);

        //  Check for the GLX_ARB_create_context extension string and the function.
        //  If either is not present, use GLX 1.3 context creation method.
        //            if ( glXCreateContextAttribsARB )
        //            {
        //                printf( "glXCreateContextAttribsARB() not found"
        //                        " ... using old-style GLX context\n" );
        //                printf("glXCreateNewContext address is %p\n", glXCreateContext);
        //                ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
        //            }

        //    // If it does, try to get a GL 3.0 context!
        //    else
        {
            int context_attribs[] =
            {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 3, 0,
                GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
                GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB
            };

            int attrib_list[] = {
                GLX_RENDER_TYPE, GLX_RGBA_TYPE,
                None
            };

            // glXCreateContextAttribs(dpy, config, share_list, direct, attrib_list);
            printf( "Creating context\n" );
            m_context = OpenGL::glXCreateContextAttribsARB( display, bestFbc, 0,
                                              True, attrib_list );

            // Sync to ensure any errors generated are processed.
            XSync( display, False );
            if ( m_context )
                printf( "Created GL 2.1 context\n" );
            else
            {
                // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
                // When a context version below 3.0 is requested, implementations will
                // return the newest context version compatible with OpenGL versions less
                // than version 3.0.
                // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
                context_attribs[1] = 1;
                // GLX_CONTEXT_MINOR_VERSION_ARB = 0
                context_attribs[3] = 0;

                printf( "Failed to create GL 3.0 context"
                        " ... using old-style GLX context\n" );
                m_context = OpenGL::glXCreateContextAttribsARB( display, bestFbc, 0,
                                                  True, context_attribs );
            }
        }

        // Sync to ensure any errors generated are processed.
        XSync( display, False );

        if (!m_context)
        {
            printf( "Failed to create an OpenGL context\n" );
            throw System::Error::SystemException("Can't create glx context");
        }

        // Verifying that context is a direct context
        if ( ! OpenGL::glXIsDirect ( display, m_context ) )
        {
            printf( "Indirect GLX rendering context obtained\n" );
        }
        else
        {
            printf( "Direct GLX rendering context obtained\n" );
        }

        printf( "Making context current\n" );
        OpenGL::glXMakeCurrent( display, m_window->GetNativeHandle(), m_context );        

#endif        

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


        //OpenGL::wglSwapIntervalEXT(0);

        const unsigned char* sv = OpenGL::glGetString(GL_SHADING_LANGUAGE_VERSION);
        m_shader_version = ((int)(sv[0]-'0'))*100;
        m_shader_version += ((int)(sv[2]-'0'))*10;
        m_shader_version += ((int)(sv[3]-'0'));

        sv = OpenGL::glGetString(GL_VERSION);
        m_opengl_version = ((int)(sv[0]-'0'))*100;
        m_opengl_version += ((int)(sv[2]-'0'))*10;
        m_opengl_version += ((int)(sv[3]-'0'));

#ifdef WIN32
        int profile;
        OpenGL::glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (profile & WGL_CONTEXT_CORE_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCore profile selected");
        if (profile & WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCompatible profile selected");
#elif defined __linux__
        int profile;
        OpenGL::glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        if (profile & GLX_CONTEXT_CORE_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCore profile selected");
        if (profile & GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB)
            m_logger->Info(L"\tCompatible profile selected");
#endif

        SubscribeResizeEvent(new Core::Action<Canvas, const System::WindowResizeEvent&>(this, &Canvas::OnResize));

        SetFullscreen(m_canvas_description.fullscreen);

        m_video_driver = System::CreateInstancePtr<IVideoDriver>(CLSID_VideoDriver, IID_IVideoDriver);
        m_video_driver->Initialize(this);

        OpenGL::glViewport(0, m_canvas_description.m_width, 0, m_canvas_description.m_height);
        OpenGL::glClearColor(0, 0, 1, 1);
        OpenGL::glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        SwapBuffers();
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
#elif defined __linux__
    void Canvas::SetVisualInfo(XVisualInfo* visual) {
        m_window->SetVisualInfo(visual);
    }

    Window Canvas::GetNativeHandle() {
        return m_window->GetNativeHandle();
    }

    Display* Canvas::GetDisplay() {
        return m_window->GetDisplay();
    }

#endif	//	 _WIN32

    PUNK_REGISTER_CREATOR(CLSID_Canvas, (System::CreateInstance<Canvas, ICanvas>));
}
PUNK_ENGINE_END
