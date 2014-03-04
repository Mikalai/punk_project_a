#ifndef GL_VIDEO_DRIVER_H
#define GL_VIDEO_DRIVER_H

#include "../../../common/video_driver.h"
#include "../../../common/video_driver_caps.h"

namespace Gpu
{
    namespace OpenGL
    {
        class GlVideoDriverProxy;

        class GlVideoDriver : public VideoDriver
        {
        public:
            GlVideoDriver();
            virtual ~GlVideoDriver();
            virtual Utility::FontBuilder* GetFontBuilder() override;
            virtual void SetFullScreen(bool flag) override;
            virtual System::Window* GetWindow() override;
            virtual Texture2D* CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) override;
            virtual Texture2DArray* CreateTexture2DArray(int width, int height, int depth, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps) override;
            virtual FrameBuffer* CreateFrameBuffer(FrameBufferConfig* config) override;
            virtual void SetViewport(float x, float y, float width, float height) override;
            virtual void SetClearColor(const Math::vec4& color) override;
            virtual void SetClearDepth(float value) override;
            virtual void Clear(bool color, bool depth, bool stencil) override;
            virtual void SwapBuffers() override;
            virtual const Config& GetConfig() const override;
            virtual size_t GetFrameBufferConfigCount() const override;
            virtual FrameBufferConfig* GetFrameBufferConfig(size_t index) override;
            virtual FrameBuffer* CreateFrameBuffer() override;
            virtual const VideoDriverSettings& GetCaps() override;

        private:
            GlVideoDriverProxy* m_driver;
        };
    }
}

#endif // GL_VIDEO_DRIVER_H
