#ifndef GL_PROXY_VIDE_DRIVER_H
#define GL_PROXY_VIDE_DRIVER_H

#include "../gl/glcorearb.h"

namespace Gpu
{
    class FrameBufferConfig;
    class VideoDriverSettings;

    namespace OpenGL
    {
        class GlTexture2D;
        class GlTexture2DArray;
        class GlFrameBuffer;                
        class GlVideoDriver;        
        class VideoMemory;

        class GlVideoDriverProxy
        {
        public:            
            virtual void SetFullScreen(bool flag) = 0;
            virtual GlTexture2D* CreateTexture2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) = 0;
            virtual GlTexture2DArray* CreateTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLint internal_format, GLint format, GLenum type, const GLvoid* data, GLboolean use_mipmaps) = 0;
            virtual GlFrameBuffer* CreateFrameBuffer(FrameBufferConfig* config) = 0;
            virtual void SetViewport(float x, float y, float width, float height) = 0;
            virtual void SetClearColor(float r, float g, float b, float a) = 0;
            virtual void SetClearDepth(float value) = 0;
            virtual void Clear(bool color, bool depth, bool stencil) = 0;
            virtual void SwapBuffers() = 0;
            virtual size_t GetFrameBufferConfigCount() const = 0;
            virtual FrameBufferConfig* GetFrameBufferConfig(size_t index) = 0;
            virtual GlFrameBuffer* CreateFrameBuffer() = 0;
            virtual const VideoDriverSettings& GetCaps() = 0;
            virtual VideoMemory* GetVideoMemory() = 0;
            virtual GlVideoDriver* GetVideoDriver() = 0;
        };
    }
}

#endif // GL_PROXY_VIDE_DRIVER_H
