#include <string.h>
#include <graphics/video_memory/module.h>
#include <graphics/frame_buffer/gl_frame_buffer/module.h>
#include <graphics/texture/module.h>
#include <graphics/video_memory/module.h>
#include <graphics/video_memory/gl_video_memory/module.h>
#include <graphics/render/module.h>
#include "gl_vfs.h"
#include "gl_video_driver.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        GlVideoDriver::GlVideoDriver(ICanvas* canvas)
            : m_canvas(canvas)
            , m_caps(new GlVideoDriverSettings(this))
            , m_memory(dynamic_cast<VideoMemory*>(Constructor::GetVideoMemory()))
        {
            m_caps->Load();
            InitVfs(this);
            InitRenderContexts(this);            
        }

        GlVideoDriver::~GlVideoDriver(){
            DestroyRenderContexts();
            delete m_caps; m_caps = nullptr;
            Constructor::DestroyVideoMemory();
        }

        bool GlVideoDriver::IsExtensionSupported(const char *extList, const char *extension) {
            const char *start;
            const char *where, *terminator;
            /* Extension names should not have spaces. */
            where = strchr(extension, ' ');
            if ( where || *extension == '\0' )
                return false;

            for ( start = extList; ; ) {
                where = strstr( start, extension );

                if ( !where )
                    break;

                terminator = where + strlen( extension );

                if ( where == start || *(where - 1) == ' ' )
                    if ( *terminator == ' ' || *terminator == '\0' )
                        return true;

                start = terminator;
            }

            return false;
        }

        OpenGL::VideoMemory* GlVideoDriver::GetVideoMemory() {
            return m_memory;
        }

        const OpenGL::VideoMemory* GlVideoDriver::GetVideoMemory() const {
            return m_memory;
        }

        ICanvas* GlVideoDriver::GetCanvas() {
            return m_canvas;
        }

        VirtualFileSystem* GlVideoDriver::GetVirtualFileSystem() {
            return m_vfs;
        }

        const VirtualFileSystem* GlVideoDriver::GetVirtualFileSystem() const {
            return m_vfs;
        }

        IVideoDriverSettings* GlVideoDriver::GetSettings()
        {
            return m_caps;
        }        
    }
	
	extern PUNK_ENGINE_API IVideoDriverUniquePtr CreateVideoDriver(ICanvas* canvas) {
		IVideoDriverUniquePtr ptr{ new OpenGL::GlVideoDriver{ canvas }, DestroyVideoDriver };
		return ptr;
	}

	extern PUNK_ENGINE_API void DestroyVideoDriver(IVideoDriver* driver) {
		OpenGL::GlVideoDriver* d = dynamic_cast<OpenGL::GlVideoDriver*>(driver);
		delete d;
	}
}


//    auto display = XOpenDisplay(NULL);
//    if (display == NULL)
//        throw System::PunkException("XWindow: can't open display");

//    static int visual_attribs[] =
//    {
//        GLX_X_RENDERABLE,       true,
//        GLX_DRAWABLE_TYPE,      GLX_WINDOW_BIT,
//        //        GLX_RENDER_TYPE,        GLX_RGBA_BIT,
//        //        GLX_X_VISUAL_TYPE,      GLX_TRUE_COLOR,
//        //        GLX_RED_SIZE,           8,
//        //        GLX_GREEN_SIZE,         8,
//        //        GLX_BLUE_SIZE,          8,
//        //        GLX_ALPHA_SIZE,         8,
//        //        GLX_DEPTH_SIZE,         24,
//        //        GLX_STENCIL_SIZE,       8,
//        //        GLX_DOUBLEBUFFER,       true,
//        None
//    };

//    int glx_major = 0, glx_minor = 0;

//    if (!glXQueryVersion(display, &glx_minor, &glx_major) ||
//            (( glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
//    {
//        printf("GLX VERSION: %d.%d\n", glx_major, glx_minor);
//        throw System::PunkException("Bad glx version");
//    }

//    int count;
//    GLXFBConfig* confs = glXGetFBConfigs(display, DefaultScreen(display), &count);
//    for (int i = 0; i != count; ++i)
//    {
//        int value;
//        out_message() << std::endl << "Config " << i+1 << "/" << count << std::endl;
//        glXGetFBConfigAttrib(display, confs[i], GLX_DRAWABLE_TYPE, &value);
//        out_message() << "GLX_DRAWABLE_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_USE_GL, &value);
//        out_message() << "GLX_USE_GL: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_BUFFER_SIZE, &value);
//        out_message() << "GLX_BUFFER_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_LEVEL, &value);
//        out_message() << "GLX_LEVEL: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_RGBA, &value);
//        out_message() << "GLX_RGBA: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_DOUBLEBUFFER, &value);
//        out_message() << "GLX_DOUBLEBUFFER: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_STEREO, &value);
//        out_message() << "GLX_STEREO: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_AUX_BUFFERS, &value);
//        out_message() << "GLX_AUX_BUFFERS: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_RED_SIZE, &value);
//        out_message() << "GLX_RED_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_BLUE_SIZE, &value);
//        out_message() << "GLX_BLUE_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_ALPHA_SIZE, &value);
//        out_message() << "GLX_ALPHA_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_DEPTH_SIZE, &value);
//        out_message() << "GLX_DEPTH_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_STENCIL_SIZE, &value);
//        out_message() << "GLX_STENCIL_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_RED_SIZE, &value);
//        out_message() << "GLX_ACCUM_RED_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_GREEN_SIZE, &value);
//        out_message() << "GLX_ACCUM_GREEN_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_BLUE_SIZE, &value);
//        out_message() << "GLX_ACCUM_BLUE_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_ACCUM_ALPHA_SIZE, &value);
//        out_message() << "GLX_ACCUM_ALPHA_SIZE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_CONFIG_CAVEAT, &value);
//        out_message() << "GLX_CONFIG_CAVEAT: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_X_VISUAL_TYPE, &value);
//        out_message() << "GLX_X_VISUAL_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_TYPE, &value);
//        out_message() << "GLX_TRANSPARENT_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_INDEX_VALUE, &value);
//        out_message() << "GLX_TRANSPARENT_INDEX_VALUE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_RED_VALUE, &value);
//        out_message() << "GLX_TRANSPARENT_RED_VALUE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_GREEN_VALUE, &value);
//        out_message() << "GLX_TRANSPARENT_GREEN_VALUE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_BLUE_VALUE, &value);
//        out_message() << "GLX_TRANSPARENT_BLUE_VALUE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_ALPHA_VALUE, &value);
//        out_message() << "GLX_TRANSPARENT_ALPHA_VALUE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_SLOW_CONFIG, &value);
//        out_message() << "GLX_SLOW_CONFIG: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRUE_COLOR, &value);
//        out_message() << "GLX_TRUE_COLOR: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_DIRECT_COLOR, &value);
//        out_message() << "GLX_DIRECT_COLOR: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_PSEUDO_COLOR, &value);
//        out_message() << "GLX_PSEUDO_COLOR: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_STATIC_COLOR, &value);
//        out_message() << "GLX_STATIC_COLOR: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_GRAY_SCALE, &value);
//        out_message() << "GLX_GRAY_SCALE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_STATIC_GRAY, &value);
//        out_message() << "GLX_STATIC_GRAY: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_RGB, &value);
//        out_message() << "GLX_TRANSPARENT_RGB: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_TRANSPARENT_INDEX, &value);
//        out_message() << "GLX_TRANSPARENT_INDEX: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_VISUAL_ID, &value);
//        out_message() << "GLX_VISUAL_ID: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_NON_CONFORMANT_CONFIG, &value);
//        out_message() << "GLX_NON_CONFORMANT_CONFIG: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_DRAWABLE_TYPE, &value);
//        out_message() << "GLX_DRAWABLE_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_RENDER_TYPE, &value);
//        out_message() << "GLX_RENDER_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_X_RENDERABLE, &value);
//        out_message() << "GLX_X_RENDERABLE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_FBCONFIG_ID, &value);
//        out_message() << "GLX_FBCONFIG_ID: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_RGBA_TYPE, &value);
//        out_message() << "GLX_RGBA_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_COLOR_INDEX_TYPE, &value);
//        out_message() << "GLX_COLOR_INDEX_TYPE: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_WIDTH, &value);
//        out_message() << "GLX_MAX_PBUFFER_WIDTH: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_HEIGHT, &value);
//        out_message() << "GLX_MAX_PBUFFER_HEIGHT: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_MAX_PBUFFER_PIXELS, &value);
//        out_message() << "GLX_MAX_PBUFFER_PIXELS: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_PRESERVED_CONTENTS, &value);
//        out_message() << "GLX_PRESERVED_CONTENTS: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_LARGEST_PBUFFER, &value);
//        out_message() << "GLX_LARGEST_PBUFFER: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_WIDTH, &value);
//        out_message() << "GLX_WIDTH: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_HEIGHT, &value);
//        out_message() << "GLX_HEIGHT: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_EVENT_MASK, &value);
//        out_message() << "GLX_EVENT_MASK: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_SAVED, &value);
//        out_message() << "GLX_SAVED: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_WINDOW, &value);
//        out_message() << "GLX_WINDOW: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER, &value);
//        out_message() << "GLX_PBUFFER: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER_HEIGHT, &value);
//        out_message() << "GLX_PBUFFER_HEIGHT: " << value << std::endl;

//        glXGetFBConfigAttrib(display, confs[i], GLX_PBUFFER_WIDTH, &value);
//        out_message() << "GLX_PBUFFER_WIDTH: " << value << std::endl;
//    }

//    int fbcount;
//    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display),
//                                         visual_attribs, &fbcount);

//    fbc = &confs[2];
//    fbcount = 1;

//    if (!fbc)
//    {
//        printf("failed to retrieve framebuffer config\n");
//        throw System::PunkException("unable to create framebuffer");
//    }

//    printf("found %d matching framebuffers", fbcount);

//    // Pick the FB config/visual with the most samples per pixel
//    printf( "Getting XVisualInfos\n" );
//    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

//    for (int i = 0; i < fbcount; i++ )
//    {
//        XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i] );
//        if ( vi )
//        {
//            int samp_buf, samples;
//            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
//            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

//            printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
//                    " SAMPLES = %d\n",
//                    i, vi -> visualid, samp_buf, samples );

//            if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
//                best_fbc = i, best_num_samp = samples;
//            if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
//                worst_fbc = i, worst_num_samp = samples;
//        }
//        XFree( vi );
//    }

//    GLXFBConfig bestFbc = fbc[ best_fbc ];

//    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
//    XFree( confs );

//    // Get a visual
//    XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc );
//    printf( "Chosen visual ID = 0x%x\n", vi->visualid );

//    printf( "Creating colormap\n" );
//    Colormap colorMap;
//    XSetWindowAttributes swa;
//    swa.colormap = colorMap = XCreateColormap( display,
//                                               RootWindow( display, vi->screen ),
//                                               vi->visual, AllocNone );
//    swa.background_pixmap = None ;
//    swa.border_pixel      = 0;
//    swa.event_mask        = KeyPressMask | PointerMotionMask | StructureNotifyMask
//            | ButtonPressMask;

//    printf( "Creating window\n" );
//    auto window = XCreateWindow( display,
//                                 RootWindow( display, vi->screen ),
//                                 0, 0, 800, 600, 0, vi->depth, InputOutput,
//                                 vi->visual,
//                                 CWBorderPixel|CWColormap|CWEventMask, &swa );
//    if ( !window )
//    {
//        printf( "Failed to create window.\n" );
//        throw System::PunkException("Can't create XWindow");
//    }

//    // Done with the visual info data
//    XFree( vi );

//    XStoreName( display, window, "GL 2.0 Window" );

//    printf( "Mapping window\n" );
//    XMapWindow(display, window);
//    printf( "Ok...\n");
//    // Get the default screen's GLX extension list
//    const char *glxExts = glXQueryExtensionsString( display, DefaultScreen( display ) );

//    printf("Extesion string is %s\n", glxExts);
//    // NOTE: It is not necessary to create or make current to a context before
//    // calling glXGetProcAddressARB
//    printf("glXGetProcAddress %p\n", glXGetProcAddress);
//    printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);

//    printf("glxCreateContextAttribsARB address is %p\n", glXCreateContextAttribsARB);

//   //  Check for the GLX_ARB_create_context extension string and the function.
//   //  If either is not present, use GLX 1.3 context creation method.
////            if ( glXCreateContextAttribsARB )
////            {
////                printf( "glXCreateContextAttribsARB() not found"
////                        " ... using old-style GLX context\n" );
////                printf("glXCreateNewContext address is %p\n", glXCreateContext);
////                ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
////            }

////    // If it does, try to get a GL 3.0 context!
////    else
//    {
//        int context_attribs[] =
//        {
//            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
//            GLX_CONTEXT_MINOR_VERSION_ARB, 3, 0,
//            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, 0,
//            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB
//        };

//        int attrib_list[] = {
//            GLX_RENDER_TYPE, render_type,
//            None
//        };

//       // glXCreateContextAttribs(dpy, config, share_list, direct, attrib_list);
//        printf( "Creating context\n" );
//        ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
//                                          True, attrib_list );

//        // Sync to ensure any errors generated are processed.
//        XSync( display, False );
//        if ( ctx )
//            printf( "Created GL 2.1 context\n" );
//        else
//        {
//            // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
//            // When a context version below 3.0 is requested, implementations will
//            // return the newest context version compatible with OpenGL versions less
//            // than version 3.0.
//            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
//            context_attribs[1] = 1;
//            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
//            context_attribs[3] = 0;

//            printf( "Failed to create GL 3.0 context"
//                    " ... using old-style GLX context\n" );
//            ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
//                                              True, context_attribs );
//        }
//    }

//    // Sync to ensure any errors generated are processed.
//    XSync( display, False );

//    if (!ctx )
//    {
//        printf( "Failed to create an OpenGL context\n" );
//        throw System::PunkException("Can't create glx context");
//    }

//    // Verifying that context is a direct context
//    if ( ! glXIsDirect ( display, ctx ) )
//    {
//        printf( "Indirect GLX rendering context obtained\n" );
//    }
//    else
//    {
//        printf( "Direct GLX rendering context obtained\n" );
//    }

//    printf( "Making context current\n" );
//    glXMakeCurrent( display, window, ctx );
PUNK_ENGINE_END
