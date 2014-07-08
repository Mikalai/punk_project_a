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
			GlTexture2DArray();
			virtual ~GlTexture2DArray();

			//	IObject
			void QueryInterface(const Core::Guid& type, void** object) override;
			std::uint32_t AddRef() override;
			std::uint32_t Release() override;
            
			//	ITexture2DArray
			void Inititalize(std::uint32_t width,
				std::uint32_t height,
				std::uint32_t size,
				ImageModule::ImageFormat internal_format,
				ImageModule::ImageFormat format,
				ImageModule::DataType type,
				const void* data,
				bool use_mipmaps,
				IVideoDriver* driver) override;

            bool IsValid() const override;
            std::uint32_t GetMemoryUsage() const override;
            void SetMinFilter(TextureFilter value) override;
            void SetMagFilter(TextureFilter value) override;
            void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) override;
            void SetCompareFunction(TextureCompareFunc value) override;
            void SetCompareMode(TextureCompareMode value) override;
            void Bind() override;
            void Bind(int slot) override;
            void Unbind() override;
            IVideoDriver* GetVideoDriver() override;
            GLuint GetId() const;

        private:
			IVideoDriver* m_video_driver{ nullptr };
			GLuint m_texture_id{ 0 };
			int m_width{ 0 };
			int m_height{ 0 };
			int m_depth{ 0 };
			int m_slot{ 0 };
			GLenum m_internal_format{ 0 };
			GLenum m_format{ 0 };
			GLenum m_type{ 0 };
			bool m_use_mip_maps{ false };
			std::atomic<std::uint32_t> m_ref_count{ 0 };
        };
    }
}
PUNK_ENGINE_END

#endif // GL_TEXTURE2D_ARRAY_H
