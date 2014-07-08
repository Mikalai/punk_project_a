#include <system/factory/module.h>
#include <system/logger/module.h>
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
    
    namespace OpenGL {

		void GlTexture2D::AssertInitialized() const {
			if (!m_initialized)
				throw Error::OpenGLException("Texture2D is not initialized");
		}

        GlTexture2D::GlTexture2D()
        {}        

		void GlTexture2D::QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ITexture2D });
		}

		std::uint32_t  GlTexture2D::AddRef() {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t  GlTexture2D::Release(){
			std::uint32_t v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

        GlTexture2D::~GlTexture2D()
        {
            Clear();
			System::GetDefaultLogger()->Debug("GlTexture2D destroyed ");
        }

        std::uint32_t GlTexture2D::GetMemoryUsage() const
        {
			AssertInitialized();
            return (std::uint32_t)(m_pbo ? m_pbo->GetSize() : 0);
        }

        void GlTexture2D::Bind()
        {
			AssertInitialized();
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void GlTexture2D::Bind(GLint slot)
        {
			AssertInitialized();
            m_bind_slot = slot;
            GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
        }

        void GlTexture2D::Unbind()
        {
			AssertInitialized();
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
			m_initialized = false;
        }

        void GlTexture2D::CopyFromCpu(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height, const void* data)
        {
			AssertInitialized();
            if (x < 0)
				throw Error::OpenGLInvalidValueException("Bad x " + Core::String::Convert(x));
            if (y < 0)
				throw Error::OpenGLInvalidValueException("Bad y " + Core::String::Convert(y));
            if (x + width > (int)m_width)
				throw Error::OpenGLInvalidValueException("Bad x offset " + Core::String::Convert(x + width) + ". Should be less or equal to " + Core::String::Convert(m_width));
            if (y + height > (int)m_height)
				throw Error::OpenGLInvalidValueException("Bad y offset " + Core::String::Convert(y + height) + ". Should be less or equal to " + Core::String::Convert(m_height));


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

		ImageModule::ImageFormat GlTexture2D::GetInternalFormat(ImageModule::ImageFormat format) {
			switch (format) {
			case ImageModule::ImageFormat::ALPHA:
			case ImageModule::ImageFormat::IMAGE_FORMAT_R32F:
			case ImageModule::ImageFormat::RED:
				return ImageModule::ImageFormat::RED;
			case ImageModule::ImageFormat::RGB:
				return ImageModule::ImageFormat::RGB;
			case ImageModule::ImageFormat::RGBA:
				return ImageModule::ImageFormat::RGBA;
			default:
				throw Error::OpenGLException(L"Can't find suitable internal format");
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
				throw Error::OpenGLInvalidImageFormat(L"Can't find suitable internal format");
            }
        }

        GLboolean GlTexture2D::Create(GLsizei width, GLsizei height, GLenum internal_format, GLenum format, GLenum type, const GLvoid* source, GLboolean use_mipmaps, IVideoDriver* driver)
        {			
			if (m_initialized)
				Clear();
			m_driver = driver;
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

			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, source));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

            //	if data available than copy them
            //if (source)
            //{
            //    void* data = Map();
            //    if (data)
            //    {
            //        memcpy(data, source, m_width * m_height * m_pixel_size);
            //        Unmap(0);
            //    }
            //}
            if (m_use_mip_maps)
                UpdateMipMaps();

			m_initialized = true;
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
                throw Error::OpenGLException(L"Texture already mapped");			
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
                throw Error::OpenGLException("Texture was not mapped");
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

		void GlTexture2D::Initialize(ImageModule::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, ImageModule::ImageFormat format, ImageModule::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver) {
			Create(width, height, Convert(internalformat), Convert(format), Convert(type), pixels, use_mipmaps, driver);
		}

		void GlTexture2D::Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) {
			return Initialize(width, height,
				internal_format, format,
				ImageModule::DataType::Byte,
				data, use_mipmaps, driver);
		}

		void GlTexture2D::Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver) {
			return Initialize(internal_format, width, height, 0, format,
				type, data, use_mipmaps, driver);
		}

		void GlTexture2D::Initialize(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) {
			auto internal_format = GetInternalFormat(format);
			return Initialize(width, height,
				internal_format, format,
				ImageModule::DataType::Byte,
				data, use_mipmaps, driver);
		}

		void GlTexture2D::Initialize(const ImageModule::IImage* image, bool use_mipmaps, IVideoDriver* driver) {
			return Initialize(image->GetWidth(),
				image->GetHeight(),
				image->GetFormat(),
				image->GetData(),
				use_mipmaps, driver);
		}

		void GlTexture2D::Initialize(const Core::String& path, bool use_mip_maps, IVideoDriver* driver)
		{
			ImageModule::IImageReaderPointer reader{ nullptr, Core::DestroyObject };
            reader = System::CreateInstancePtr<ImageModule::IImageReader>(ImageModule::IID_IImageReader);
			ImageModule::IImage* image = reader->Read(path);
			return Initialize(image, use_mip_maps, driver);
		}

		void GlTexture2D::Initialize(Core::Buffer *buffer, bool use_mip_maps, IVideoDriver* driver)
		{
			ImageModule::IImageReaderPointer reader{ nullptr, Core::DestroyObject };
            reader = System::CreateInstancePtr<ImageModule::IImageReader>(ImageModule::IID_IImageReader);
			ImageModule::IImagePointer image{ reader->Read(*buffer), Core::DestroyObject };
			return Initialize(image.get(), use_mip_maps, driver);
		}

		void GlTexture2D::Initialize(const ImageModule::IImage* image, ImageModule::ImageFormat internal_format, bool use_mipmaps, IVideoDriver* driver)
		{
			auto format = GetInternalFormat(image->GetFormat());
			size_t width = image->GetWidth();
			size_t height = image->GetHeight();
			void* data = (void*)image->GetData();
			Initialize((int)width, (int)height, internal_format, format, data, use_mipmaps, driver);
		}
    }   

	PUNK_REGISTER_CREATOR(IID_ITexture2D, (System::CreateInstance<OpenGL::GlTexture2D, ITexture2D>));
}
PUNK_ENGINE_END
