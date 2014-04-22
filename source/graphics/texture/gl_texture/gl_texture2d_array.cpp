#include <graphics/texture/module.h>
#include <graphics/video_driver/module.h>
#include "gl_texture_convert.h"
#include "gl_texture2d_array.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        GlTexture2DArray::GlTexture2DArray(std::uint32_t width,
                                           std::uint32_t height,
                                           std::uint32_t size,
                                           Image::ImageFormat internal_format,
                                           Image::ImageFormat format,
                                           Image::DataType type,
                                           const void* data,
                                           bool use_mipmaps,
                                           IVideoDriver* driver)
            : m_video_driver(driver)
            , m_width(width)
            , m_height(height)
            , m_depth(size)
            , m_internal_format(Convert(internal_format))
            , m_format(Convert(format))
            , m_type(Convert(type))
            , m_use_mip_maps(use_mipmaps)
            , m_texture_id(0)
            , m_slot(0) {
            GL_CALL(glGenTextures(1, &m_texture_id));
            Bind();
            GL_CALL(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, m_internal_format, m_width, m_height, m_depth, 0, m_format, m_type, data));
            Unbind();
        }

        GlTexture2DArray::~GlTexture2DArray() {
            GL_CALL(glDeleteTextures(1, &m_texture_id));
            m_texture_id = 0;
        }

        bool GlTexture2DArray::IsValid() const {
            return m_texture_id != 0;
        }

        std::uint32_t GlTexture2DArray::GetMemoryUsage() const {
            return m_width * m_height * m_depth * 4;    //  TODO: Should be something better
        }

        void GlTexture2DArray::SetMinFilter(TextureFilter value) {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, Convert(value)));
            Unbind();
        }

        void GlTexture2DArray::SetMagFilter(TextureFilter value) {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, Convert(value)));
            Unbind();
        }

        void GlTexture2DArray::SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, Convert(dir), Convert(mode)));
            Unbind();
        }

        void GlTexture2DArray::SetCompareFunction(TextureCompareFunc value) {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, Convert(value)));
            Unbind();
        }

        void GlTexture2DArray::SetCompareMode(TextureCompareMode value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, Convert(value)));
            Unbind();
        }

        void GlTexture2DArray::Bind()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture_id));
        }

        void GlTexture2DArray::Bind(int slot)
        {
            m_slot = slot;
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
            Bind();
        }

        void GlTexture2DArray::Unbind()
        {
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
        }

        IVideoDriver* GlTexture2DArray::GetVideoDriver()
        {
            return m_video_driver;
        }

        GLuint GlTexture2DArray::GetId() const
        {
            return m_texture_id;
        }
    }

    extern PUNK_ENGINE_API ITexture2DArrayUniquePtr CreateTexture2DArray(std::uint32_t width, std::uint32_t height, std::uint32_t size, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void *data, bool use_mipmaps, IVideoDriver *driver) {
        return ITexture2DArrayUniquePtr{new OpenGL::GlTexture2DArray(width, height, size, internal_format, format, type, data, use_mipmaps, driver), DestroyTexture2DArray};
    }

    extern PUNK_ENGINE_API void DestroyTexture2DArray(ITexture2DArray* value) {
        OpenGL::GlTexture2DArray* texture = dynamic_cast<OpenGL::GlTexture2DArray*>(value);
        delete texture;
    }
}
PUNK_ENGINE_END

