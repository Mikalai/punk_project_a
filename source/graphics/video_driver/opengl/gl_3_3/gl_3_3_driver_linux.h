#ifndef _H_PUNK_OPENGL_DRIVER_LINUX
#define _H_PUNK_OPENGL_DRIVER_LINUX

#include "../../../../config.h"
#include "../common/gl_video_driver.h"

namespace Gpu
{
    class FrameBufferConfig;
    class Texture2DArray;
    class Texture2D;
    class FrameBuffer;
    class VideoMemory;

    namespace OpenGL
    {
        class VirtualFileSystem;

        class PUNK_ENGINE_LOCAL GlVideoDriver_3_3 : public GlVideoDriverProxy
        {
        public:
            //	constructoion part
            GlVideoDriver_3_3(const VideoDriverDesc& desc);
            virtual ~GlVideoDriver_3_3();

            bool IsExtensionSupported(const char *extList, const char *extension);
            void InitExtensions();
            void InitGlxFunctions();            
            int* GetVisualAttributes();
            int* GetContextAttributes();            
            void BindWindow(System::Window* window);
            VideoMemory* GetVideoMemory();
            const VideoMemory* GetVideoMemory() const;
            VirtualFileSystem* GetVirtualFileSystem();
            const VirtualFileSystem* GetVirtualFileSystem() const;


        private:

            int m_shader_version;
            int m_opengl_version;                        
            VideoDriverDesc m_desc;            
            OpenGL::VideoMemory* m_memory;            
            std::vector<FrameBufferConfig> m_fb_config;
            std::vector<OpenGL::OpenGLFrameBuffer*> m_frame_buffer;
            VideoDriverSettings m_caps;
            VirtualFileSystem* m_vfs;

        private:
            void Init();
            void Clear();
            void ReadConfig();
            void InitShaderPrograms();
            void SubscribeForSystemMessages();
            void InitInternalVertexBuffers();
        };
    }
}

#endif	//	_H_PUNK_OPENGL_DRIVER_LINUX
