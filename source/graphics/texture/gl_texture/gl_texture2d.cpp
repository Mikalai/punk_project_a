#include <graphics/video_memory/gl_video_memory/module.h>
#include <graphics/buffers/module.h>
#include <graphics/opengl/module.h>
#include <graphics/error/module.h>
#include <graphics/video_driver/gl_video_driver/module.h>
#include <images/module.h>
#include "gl_texture_convert.h"
#include "gl_texture2d.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    Image::ImageFormat GetInternalFormat(Image::ImageFormat format) {
        switch(format) {
        case Image::ImageFormat::ALPHA:
        case Image::ImageFormat::IMAGE_FORMAT_R32F:
        case Image::ImageFormat::RED:
            return Image::ImageFormat::RED;
        case Image::ImageFormat::RGB:
            return Image::ImageFormat::RGB;
        case Image::ImageFormat::RGBA:
            return Image::ImageFormat::RGBA;
        default:
            throw Error::GraphicsException(L"Can't find suitable internal format");
        }
    }

    namespace OpenGL {

        GlTexture2D::GlTexture2D(IVideoDriver* driver)
            : m_driver(dynamic_cast<GlVideoDriver*>(driver))
        {}

        GlTexture2D::GlTexture2D(GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels, GLboolean use_mipmaps, IVideoDriver *driver)
            : m_driver(dynamic_cast<GlVideoDriver*>(driver))
        {
            Create(width, height, internal_format, format, type, pixels, use_mipmaps);
        }

        GlTexture2D::~GlTexture2D()
        {
            Clear();
        }

        std::uint32_t GlTexture2D::GetMemoryUsage() const
        {
            return (std::uint32_t)(m_pbo ? m_pbo->GetSize() : 0);
        }

        void GlTexture2D::Bind()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void GlTexture2D::Bind(GLint slot)
        {
            m_bind_slot = slot;
            GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void GlTexture2D::Unbind()
        {
            GL_CALL(glActiveTexture(GL_TEXTURE0 + m_bind_slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
        }

        void GlTexture2D::Clear()
        {
			if (m_pbo && m_pbo->Release())
				m_pbo = nullptr;

            if (m_texture_id)
            {
                GL_CALL(glDeleteTextures(1, &m_texture_id));
                m_texture_id = 0;
            }
        }

        void GlTexture2D::CopyFromCpu(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height, const void* data)
        {
            if (x < 0)
                throw OpenGLInvalidValueException("Bad x " + Core::String::Convert(x));
            if (y < 0)
                throw OpenGLInvalidValueException("Bad y " + Core::String::Convert(y));
            if (x + width > (int)m_width)
                throw OpenGLInvalidValueException("Bad x offset " + Core::String::Convert(x + width) + ". Should be less or equal to " + Core::String::Convert(m_width));
            if (y + height > (int)m_height)
                throw OpenGLInvalidValueException("Bad y offset " + Core::String::Convert(y + height) + ". Should be less or equal to " + Core::String::Convert(m_height));


            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, m_format, m_internal_type, data));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));


            if (m_use_mip_maps)
            {
                GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
                GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
                GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
            }
        }

        void GlTexture2D::Resize(std::uint32_t width, std::uint32_t height) {
            if (m_texture_id != 0) {
                GL_CALL(glDeleteTextures(1, &m_texture_id));
            }

            m_width = width;
            m_height = height;
            GL_CALL(glGenTextures(1, &m_texture_id));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_internal_format, m_internal_type, 0));
            Fill(0);
        }

        GLsizei GlTexture2D::GetPixelSize(GLenum format)
        {
            switch(format)
            {
            case GL_RED:
                return 1;
            case GL_RGB:
                return 3;
            case GL_RGBA:
            case GL_RGBA8:
            case GL_R32F:
                return 4;
            case GL_DEPTH_COMPONENT16:
                return 2;
            case GL_DEPTH_COMPONENT24:
                return 3;
            case GL_DEPTH_COMPONENT32:
                return 4;
            default:
                return 0;
            }
        }

        GLenum GlTexture2D::GetInternalFormat(GLenum format)
        {
            switch(format)
            {
            case GL_RED:
            case GL_ALPHA:
            case GL_R32F:
                return GL_RED;
            case GL_RGB:
                return GL_RGB;
            case GL_RGBA:
                return GL_RGBA;
            case GL_DEPTH_COMPONENT16:
            case GL_DEPTH_COMPONENT24:
            case GL_DEPTH_COMPONENT32:
                return GL_DEPTH_COMPONENT;
            default:
                throw OpenGLInvalidImageFormat(L"Can't find suitable internal format");
            }
        }

        GLboolean GlTexture2D::Create(GLsizei width, GLsizei height, GLenum internal_format, GLenum format, GLenum type, const GLvoid* source, GLboolean use_mipmaps)
        {
            m_width = width;
            m_height = height;
            m_internal_format = internal_format;
            m_format = format;
            m_use_mip_maps = use_mipmaps;
            m_pixel_size = GetPixelSize(internal_format);
            m_internal_type = type;

            GL_CALL(glGenTextures(1, &m_texture_id));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));

            if (use_mipmaps)
            {
                GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            }
            else
            {
                GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            }

            GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT));

            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, 0));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

            //	if data available than copy them
            if (source)
            {
                void* data = Map();
                if (data)
                {
                    memcpy(data, source, m_width * m_height * m_pixel_size);
                    Unmap(0);
                }
            }
            if (m_use_mip_maps)
                UpdateMipMaps();

            return true;
        }

        void GlTexture2D::UpdateMipMaps()
        {
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
        }

        void* GlTexture2D::Map()
        {
            if (m_pbo)
                throw OpenGLException(L"Texture already mapped");			
			m_pbo = new PixelBufferObject<std::uint8_t>();
			m_pbo->Create(nullptr, m_width*m_height*m_pixel_size);
            void* ptr = m_pbo->Map();
			if (!ptr)
				m_pbo->Release();
            return ptr;
        }

        void GlTexture2D::Unmap(void*)
        {
            if (!m_pbo)
                throw OpenGLException("Texture was not mapped");
            m_pbo->Unmap();
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
            m_pbo->Bind();
            GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_internal_format, m_internal_type, 0));
            m_pbo->Unbind();
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

			if (!m_pbo->Release())
				m_pbo = nullptr;

            if (m_use_mip_maps)
                UpdateMipMaps();
        }

        void GlTexture2D::Fill(unsigned char byte)
        {
            void* dst = Map();
            if (dst)
            {
                memset(dst, byte, m_width*m_height*m_pixel_size);
                Unmap(dst);

                if (m_use_mip_maps)
                    UpdateMipMaps();
            }
        }

        void GlTexture2D::SetMinFilter(TextureFilter value) {
            SetMinFilter(Convert(value));
        }

        void GlTexture2D::SetMinFilter(GLenum value) {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, value));
            Unbind();
        }

        void GlTexture2D::SetMagFilter(TextureFilter value) {
            SetMagFilter(Convert(value));
        }

        void GlTexture2D::SetMagFilter(GLenum value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, value));
            Unbind();
        }

        void GlTexture2D::SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) {
            SetWrapMode(Convert(dir), Convert(mode));
        }

        void GlTexture2D::SetWrapMode(GLenum dir, GLenum mode)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, dir, mode));
            Unbind();
        }

        void GlTexture2D::SetCompareFunction(TextureCompareFunc value) {
            SetCompareFunction(Convert(value));
        }

        void GlTexture2D::SetCompareFunction(GLenum value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, value));
            Unbind();
        }

        void GlTexture2D::SetCompareMode(TextureCompareMode value) {
            SetCompareFunction(Convert(value));
        }

        void GlTexture2D::SetCompareMode(GLenum value)
        {
            Bind();
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, value));
            Unbind();
        }

        std::uint32_t GlTexture2D::GetHeight() const
        {
            return m_width;
        }

        std::uint32_t GlTexture2D::GetWidth() const
        {
            return m_height;
        }

        GLuint GlTexture2D::GetIndex() const
        {
            return m_texture_id;
        }

        bool GlTexture2D::IsValid() const
        {
            return m_texture_id != 0;
        }

        IVideoDriver* GlTexture2D::GetVideoDriver()
        {
            return m_driver;
        }
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(Image::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, Image::ImageFormat format, Image::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver) {
        using namespace OpenGL;
        return ITexture2DUniquePtr{new GlTexture2D(Convert(internalformat), width, height, border, Convert(format), Convert(type), pixels, use_mipmaps, driver), DestroyTexture2D};
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) {
        return CreateTexture2D(width, height,
                               internal_format, format,
                               Image::DataType::IMAGE_DATA_TYPE_BYTE,
                               data, use_mipmaps, driver);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver) {
        return Graphics::CreateTexture2D(internal_format, width, height, 0, format,
                                            type, data, use_mipmaps, driver);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, Image::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) {
        auto internal_format = GetInternalFormat(format);
        return CreateTexture2D(width, height,
                               internal_format, format,
                               Image::DataType::IMAGE_DATA_TYPE_BYTE,
                               data, use_mipmaps, driver);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const Image::Image& image, bool use_mipmaps, IVideoDriver* driver) {
        return CreateTexture2D(image.GetWidth(),
                               image.GetHeight(),
                               image.GetImageFormat(),
                               image.GetData(),
                               use_mipmaps, driver);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const Core::String& path, bool use_mip_maps, IVideoDriver* driver)
    {
        Image::Importer importer;
        std::unique_ptr<Image::Image> image(importer.LoadAnyImage(path));

        if (image.get())
        {
            return CreateTexture2D(*image, use_mip_maps, driver);
        }
        else
            throw Error::GraphicsException(L"Can't create texture from " + path);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(Core::Buffer *buffer, bool use_mip_maps, IVideoDriver* driver)
    {
        Image::Image image;
        image.Load(buffer);
        return CreateTexture2D(image, use_mip_maps, driver);
    }

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const Image::Image &image, Image::ImageFormat internal_format, bool use_mipmaps, IVideoDriver* driver)
    {
        auto format = GetInternalFormat(image.GetImageFormat());
        size_t width = image.GetWidth();
        size_t height = image.GetHeight();
        void* data = (void*)image.GetData();
        std::vector<unsigned char> buffer(image.GetSizeInBytes());
        memcpy(&buffer[0], data, image.GetSizeInBytes());
        return CreateTexture2D((int)width, (int)height, internal_format, format, data, use_mipmaps, driver);
    }


    extern "C" PUNK_ENGINE_API void DestroyTexture2D(ITexture2D* value) {
        using namespace OpenGL;
        GlTexture2D* texture = dynamic_cast<GlTexture2D*>(value);
        delete texture;
    }
}
PUNK_ENGINE_END
