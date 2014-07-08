#ifndef GL_TEXTURE2D_H
#define GL_TEXTURE2D_H

#include <graphics/texture/module.h>
#include <graphics/opengl/module.h>
#include <graphics/buffers/pbo.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        class GlVideoDriver;

        class PUNK_ENGINE_LOCAL GlTexture2D : public ITexture2D {
        public:
            GlTexture2D();
            virtual ~GlTexture2D();

			//	IObject
			void QueryInterface(const Core::Guid& type, void** object) override;
			std::uint32_t AddRef() override;
			std::uint32_t Release() override;

			//	ITexture
            bool IsValid() const override;
            std::uint32_t GetMemoryUsage() const override;
            void SetMinFilter(TextureFilter value) override;
            void SetMagFilter(TextureFilter value) override;
            void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            void SetCompareFunction(TextureCompareFunc value) override;
            void SetCompareMode(TextureCompareMode value) override;
            void Bind() override;
            void Bind(std::int32_t slot) override;
            void Unbind() override;
            IVideoDriver* GetVideoDriver() override;

			//	ITexture2D
			void Initialize(ImageModule::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, ImageModule::ImageFormat format, ImageModule::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(const ImageModule::IImage* image, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(const Core::String& path, bool use_mipmaps, IVideoDriver* driver) override;
			void Initialize(Core::Buffer* buffer, bool use_mip_maps, IVideoDriver* driver) override;
			void Initialize(const ImageModule::IImage* mage, ImageModule::ImageFormat internal_format, bool use_mipmaps, IVideoDriver* driver) override;
            void CopyFromCpu(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height, const void* data) override;
            void Resize(std::uint32_t width, std::uint32_t height) override;
            void Fill(std::uint8_t data) override;
            std::uint32_t GetHeight() const override;
            std::uint32_t GetWidth() const override;
            void* Map() override;
            void Unmap(void* data) override;


            void SetMinFilter(GLenum value);
            void SetMagFilter(GLenum value);
            void SetWrapMode(GLenum  dir, GLenum mode);
            void SetCompareFunction(GLenum value);
            void SetCompareMode(GLenum value);

            static GLsizei GetPixelSize(GLenum format);
            static GLenum GetInternalFormat(GLenum format);
			static ImageModule::ImageFormat GetInternalFormat(ImageModule::ImageFormat format);
			GLboolean Create(GLsizei width, GLsizei height, GLenum internal_format, GLenum format, GLenum type, const GLvoid* source, GLboolean use_mipmaps, IVideoDriver* driver);
            void Clear();
            void UpdateMipMaps();
            GLuint GetIndex() const;
        private:
			void AssertInitialized() const;
		private:
			bool m_initialized = false;
            IVideoDriver* m_driver {nullptr};
            IBufferObject* m_pbo {nullptr};
            GLuint m_texture_id {0};
            GLsizei m_width {0};
            GLsizei m_height {0};
            GLint m_pixel_size {0};
            GLint m_bind_slot {0};
            GLboolean m_use_mip_maps {0};
            GLenum m_format {0};
            GLenum m_internal_format {0};
            GLenum m_internal_type {0};
			std::atomic<std::uint32_t> m_ref_count{ 0 };
        };
    }
}
PUNK_ENGINE_END

#endif // GL_TEXTURE2D_H
