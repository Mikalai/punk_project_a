#ifndef _H_PUNK_OPENGL_DRIVER
#define _H_PUNK_OPENGL_DRIVER

#include <vector>
#include <config.h>
#include <graphics/video_driver/module.h>
#include <graphics/video_driver/video_driver.h>
#include "gl_settings.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class Texture2DArray;
    class Texture2D;
    class FrameBuffer;
    class VideoMemory;

    namespace OpenGL {

        class VideoMemory;
        class GlVideoDriverSettings;
        class VirtualFileSystem;
        class GlFrameBuffer;

        class PUNK_ENGINE_LOCAL GlVideoDriver : public VideoDriver {
        public:
            //	constructoion part
            GlVideoDriver(ICanvas* canvas);
            virtual ~GlVideoDriver();
            ICanvas* GetCanvas() override;                        
            IVideoDriverSettings* GetSettings() override;

            VideoMemory* GetVideoMemory();
            const VideoMemory* GetVideoMemory() const;
            VirtualFileSystem* GetVirtualFileSystem();
            const VirtualFileSystem* GetVirtualFileSystem() const;
            bool IsFeatureSupported(const char* feature);

        private:

            int m_shader_version;
            int m_opengl_version;
            ICanvas* m_canvas {nullptr};
            OpenGL::VideoMemory* m_memory;            
            VirtualFileSystem* m_vfs;
            GlVideoDriverSettings* m_caps;

        private:
            bool IsExtensionSupported(const char *extList, const char *extension);
            void Init();
            void Clear();
            void ReadConfig();
            void InitShaderPrograms();
            void SubscribeForSystemMessages();
            void InitInternalVertexBuffers();
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_DRIVER_LINUX
