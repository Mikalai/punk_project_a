#ifndef GL_TEXTURE2D_ARRAY_H
#define GL_TEXTURE2D_ARRAY_H

#include <graphics/texture/itexture2d_array.h>
#include <graphics/opengl/module.h>
#include <images/formats.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        class PUNK_ENGINE_LOCAL GlTexture2DArray : public ITexture2DArray {
        public:
            GlTexture2DArray(const GlTexture2DArray&) = delete;
            GlTexture2DArray& operator = (const GlTexture2DArray&) = delete;
            GlTexture2DArray(std::uint32_t width, std::uint32_t height, std::uint32_t size, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver);
            virtual ~GlTexture2DArray();
            virtual bool IsValid() const override;
            virtual std::uint32_t GetMemoryUsage() const override;
            virtual void SetMinFilter(TextureFilter value) override;
            virtual void SetMagFilter(TextureFilter value) override;
            virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            virtual void SetCompareFunction(TextureCompareFunc value) override;
            virtual void SetCompareMode(TextureCompareMode value) override;
            virtual void Bind() override;
            virtual void Bind(int slot) override;
            virtual void Unbind() override;
            virtual IVideoDriver* GetVideoDriver() override;
            GLuint GetId() const;

        private:
            IVideoDriver* m_video_driver;
            GLuint m_texture_id;
            int m_width;
            int m_height;
            int m_depth;
            int m_slot;
            GLenum m_internal_format;
            GLenum m_format;
            GLenum m_type;
            bool m_use_mip_maps;
        };
    }
}
PUNK_ENGINE_END

#endif // GL_TEXTURE2D_ARRAY_H
