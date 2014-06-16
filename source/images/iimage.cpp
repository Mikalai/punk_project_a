#include <core/ifactory.h>
#include "iimage.h"


PUNK_ENGINE_BEGIN
namespace ImageModule {

	extern Core::Guid GetImageFormatGuid(ImageFormat format);

	template<ImageFormat Format>
	class Image : public IImage {
	public:

		virtual ~Image() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IImage, GetImageFormatGuid(Format) });
		}

		std::uint32_t AddRef() override {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t Release() override {
			std::uint32_t value = m_ref_count;
			if (!(m_ref_count.fetch_sub(1)-1)) {
				delete this;
			}
			value--;
			return value;
		}

		void SetSize(std::uint32_t width, std::uint32_t height) {
			m_width = width;
			m_height = height;
			m_data.resize(m_width*m_height*Pixel<Format>::GetSize());
		}

		//	IImage
		std::uint32_t GetWidth() const override {
			return m_width;
		}

		std::uint32_t GetHeight() const override {
			return m_height;
		}

		ImageFormat GetFormat() const override {
			return Format;
		}

		const void* GetData() const override {
			return m_data.data();
		}

		void* GetData() override {
			return m_data.data();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		std::uint32_t m_width;
		std::uint32_t m_height;
		//ImageFormat m_format;
		std::vector<std::uint8_t> m_data;
	};	

	static Core::Guid GetImageFormatGuid(ImageFormat format) {
		switch (format)
		{
		case ImageFormat::IMAGE_FORMAT_ALPHA4:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA12:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA16:
			break;
		case ImageFormat::DepthComponent:
			break;
		case ImageFormat::DEPTH_COMPONENT16:
			break;
		case ImageFormat::DEPTH_COMPONENT24:
			break;
		case ImageFormat::IMAGE_FORMAT_DEPTH_COMPONENT32:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE4:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE8:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE12:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE16:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE4_ALPHA4:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE6_ALPHA2:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE8_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE12_ALPHA4:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE12_ALPHA12:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE16_ALPHA16:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY4:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY8:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY12:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY16:
			break;
		case ImageFormat::IMAGE_FORMAT_R3_G3_B2:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB4:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB5:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB8:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB10:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB12:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB16:
			break;
		case ImageFormat::RGBA2:
			break;
		case ImageFormat::RGBA4:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB5_A1:
			break;
		case ImageFormat::RGBA8:
			break;
		case ImageFormat::RGB10_A2:
			break;
		case ImageFormat::RGBA12:
			break;
		case ImageFormat::RGBA16:
			break;
		case ImageFormat::RGBA16F:
			break;
		case ImageFormat::RGBA32F:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX1:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX2:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX4:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX8:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX12:
			break;
		case ImageFormat::IMAGE_FORMAT_COLOR_INDEX16:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_LUMINANCE8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_RGB8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_RGBA8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_INTENSITY8:
			break;
		case ImageFormat::IMAGE_FORMAT_HILO16:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_HILO16:
			break;
		case ImageFormat::IMAGE_FORMAT_DSDT8:
			break;
		case ImageFormat::IMAGE_FORMAT_DSDT8_MAG8:
			break;
		case ImageFormat::IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8:
			break;
		case ImageFormat::IMAGE_FORMAT_HILO8:
			break;
		case ImageFormat::IMAGE_FORMAT_SIGNED_HILO8:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_R16:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_R32:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RG16:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RGB16:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RGBA16:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RG32:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RGB32:
			break;
		case ImageFormat::IMAGE_FORMAT_FLOAT_RGBA32:
			break;
		case ImageFormat::RGBA_FLOAT32:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB_FLOAT32:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA_FLOAT32:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY_FLOAT32:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_FLOAT32:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32:
			break;
		case ImageFormat::RGBA_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16:
			break;
		case ImageFormat::IMAGE_FORMAT_DEPTH24_STENCIL8:
			break;
		case ImageFormat::DEPTH_COMPONENT32F:
			break;
		case ImageFormat::IMAGE_FORMAT_DEPTH32F_STENCIL8:
			break;
		case ImageFormat::IMAGE_FORMAT_SRGB8:
			break;
		case ImageFormat::SRGB8_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_SLUMINANCE8:
			break;
		case ImageFormat::IMAGE_FORMAT_SLUMINANCE8_ALPHA8:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB9_E5:
			break;
		case ImageFormat::R11F_G11F_B10F:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2:
			break;
		case ImageFormat::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2:
			break;
		case ImageFormat::RGBA32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA32UI:
			break;
		case ImageFormat::RGBA16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA16UI:
			break;
		case ImageFormat::RGBA8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA8UI:
			break;
		case ImageFormat::RGBA32I:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB32I:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA32I:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY32I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE32I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA32I:
			break;
		case ImageFormat::RGBA16I:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB16I:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA16I:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY16I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE16I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA16I:
			break;
		case ImageFormat::RGBA8I:
			break;
		case ImageFormat::IMAGE_FORMAT_RGB8I:
			break;
		case ImageFormat::IMAGE_FORMAT_ALPHA8I:
			break;
		case ImageFormat::IMAGE_FORMAT_INTENSITY8I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE8I:
			break;
		case ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA8I:
			break;
		case ImageFormat::IMAGE_FORMAT_RG32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_R32UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RG16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_R16UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RG8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_R8UI:
			break;
		case ImageFormat::IMAGE_FORMAT_RG32I:
			break;
		case ImageFormat::IMAGE_FORMAT_R32I:
			break;
		case ImageFormat::IMAGE_FORMAT_RG16I:
			break;
		case ImageFormat::IMAGE_FORMAT_R16I:
			break;
		case ImageFormat::IMAGE_FORMAT_RG8I:
			break;
		case ImageFormat::IMAGE_FORMAT_R8I:
			break;
		case ImageFormat::IMAGE_FORMAT_RG8:
			break;
		case ImageFormat::IMAGE_FORMAT_R8:
			break;
		case ImageFormat::IMAGE_FORMAT_RG16:
			break;
		case ImageFormat::IMAGE_FORMAT_R16:
			break;
		case ImageFormat::IMAGE_FORMAT_RG16F:
			break;
		case ImageFormat::IMAGE_FORMAT_R16F:
			break;
		case ImageFormat::IMAGE_FORMAT_RG32F:
			break;
		case ImageFormat::IMAGE_FORMAT_R32F:
			break;
		case ImageFormat::IMAGE_FORMAT_BGRA:
			break;
		case ImageFormat::IMAGE_FORMAT_BGR:
			break;
		case ImageFormat::ALPHA:
			break;
		case ImageFormat::RGBA:
			return IID_IRgbaImage;
		case ImageFormat::RGB:
			break;
		case ImageFormat::RED:
			break;
		case ImageFormat::BAD:
			break;
		default:
			break;
		}
		return Core::Guid::Empty();
	}

	PUNK_REGISTER_CREATOR(IID_IRgbaImage, (Core::CreateInstance < Image<ImageFormat::RGBA>, IImage>));
	PUNK_REGISTER_CREATOR(IID_IRgbImage, (Core::CreateInstance < Image<ImageFormat::RGB>, IImage>));
	PUNK_REGISTER_CREATOR(IID_IAlphaImage, (Core::CreateInstance < Image<ImageFormat::ALPHA>, IImage>));
}
PUNK_ENGINE_END
