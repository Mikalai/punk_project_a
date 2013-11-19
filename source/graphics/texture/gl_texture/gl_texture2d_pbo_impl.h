#ifndef _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
#define _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL

#include <memory.h>
#include "../../../../../config.h"
#include "../../gl/glcorearb.h"

namespace Gpu
{
    namespace OpenGL
    {
        class PixelBufferObject;
        class GlVideoDriverProxy;

        class PUNK_ENGINE_LOCAL GlTexture2DImpl
        {
        public:
            GlTexture2DImpl(GlVideoDriverProxy* driver);
            GlTexture2DImpl(GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels, GLboolean use_mipmaps, GlVideoDriverProxy* driver);
            ~GlTexture2DImpl();
            void Bind();
            void Bind(GLint slot);
            void Unbind();
            void CopyFromCpu(GLint x, GLint y, GLsizei width, GLsizei height, const GLvoid* data);
            void Resize(GLsizei width, GLsizei height);
            void Fill(GLubyte data);
            GLsizei GetHeight() const;
            GLsizei GetWidth() const;
            GLvoid* Map();
            void Unmap(GLvoid*);
            GLboolean IsValid() const;
            GLsizei GetMemoryUsage() const;
            void SetMinFilter(GLenum value);
            void SetMagFilter(GLenum value);
            void SetWrapMode(GLenum dir, GLenum mode);
            void SetCompareFunction(GLenum value);
            void SetCompareMode(GLenum value);
            GlVideoDriverProxy* GetVideoDriver();

            GLsizei GetPixelSize(GLenum format);
            GLenum GetInternalFormat(GLenum format);
            GLboolean Create(GLsizei width, GLsizei height, GLenum internal_format, GLenum format, GLenum type, const GLvoid* source, GLboolean use_mipmaps);
            void Clear();
            void UpdateMipMaps();
            GLuint GetIndex() const;
        private:

            GlVideoDriverProxy* m_driver {nullptr};
            PixelBufferObject* m_pbo {nullptr};
            GLuint m_texture_id {0};
            GLsizei m_width {0};
            GLsizei m_height {0};
            GLint m_pixel_size {0};
            GLint m_bind_slot {0};
            GLboolean m_use_mip_maps {0};
            GLenum m_format {0};
            GLenum m_internal_format {0};
            GLenum m_internal_type {0};
        };
    }
}

#endif	//	_H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
