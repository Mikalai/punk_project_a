#include "rgb_image.h"
#include "image_impl.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	RGBImage::RGBImage()
		: Image()
	{
        impl_image->m_channels = 3;
		impl_image->m_format = IMAGE_FORMAT_RGB;
        impl_image->m_component_type = ComponentType::UnsignedByte;
	}

	RGBImage::RGBImage(const RGBImage& image)
		: Image(image)
	{}

	RGBImage& RGBImage::operator = (const RGBImage& image)
	{
		Image::operator= (image);
		return *this;
	}
}
PUNK_ENGINE_END
