#ifndef GL_TEXTURE2D_H
#define GL_TEXTURE2D_H

#include "gpu/common/texture/texture2d.h"

namespace Gpu
{
    namespace OpenGL
    {
        class GlTexture2DImpl;

        class GlTexture2D : public Texture2D
        {
        public:
            GlTexture2D();
            GlTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, VideoDriver* driver);
            virtual ~GlTexture2D();
            virtual void Bind() override;
            virtual void Bind(int slot) override;
            virtual void Unbind() override;
            virtual void CopyFromCpu(int x, int y, int width, int height, const void* data) override;
            virtual void Resize(int width, int height) override;
            virtual void Fill(unsigned char data) override;
            virtual int GetHeight() const override;
            virtual int GetWidth() const override;
            virtual void* Map() override;
            virtual void Unmap(void* data) override;
            virtual bool IsValid() const override;
            virtual size_t GetMemoryUsage() const override;
            virtual void SetMinFilter(TextureFilter value) override;
            virtual void SetMagFilter(TextureFilter value) override;
            virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            virtual void SetCompareFunction(TextureCompareFunc value) override;
            virtual void SetCompareMode(TextureCompareMode value) override;
            virtual VideoDriver* GetVideoDriver() override;
        private:
            GlTexture2DImpl* m_impl;
        };
    }
}

#endif // GL_TEXTURE2D_H
