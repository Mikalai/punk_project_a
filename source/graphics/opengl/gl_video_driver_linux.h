#ifndef GL_VIDEO_DRIVER_LINUX_H
#define GL_VIDEO_DRIVER_LINUX_H

#include <dlfcn.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "gl_proxy_video_driver.h"

namespace Gpu
{
    namespace OpenGL
    {
        class GlVideoDriverLinux : public GlVideoDriverProxy
        {
        public:
            GlVideoDriverLinux();

            void SelectVisualInfo();
            void CreateOpenGLContext();
            void CreateOpenGLWindow();
            void StartLinuxDriver();
            void ShutdownLinuxDriver();
            int GetGlxMinorVersion();
            int GetGlxMajorVersion();
            Display* GetDisplay();
            GLXFBConfig* ChooseConfis(Display* display, Window window);

        private:
            int m_glx_version;
            __GLXcontextRec* ctx;
            GLXFBConfig m_best_fbc;
            Display* m_display;
            Window m_window;
            XVisualInfo* m_visual_info;
            int m_glx_minor_version;
            int m_glx_major_version;
            XF86VidModeModeInfo m_default_mode;
        };
    }
}
#endif // GL_VIDEO_DRIVER_LINUX_H
