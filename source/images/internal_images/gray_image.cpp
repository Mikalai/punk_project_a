#include "gray_image.h"
#include "image_impl.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	GrayImage::GrayImage()
		: Image()
	{
        impl_image->m_channels = 1;
		impl_image->m_format = IMAGE_FORMAT_ALPHA;
        impl_image->m_component_type = ComponentType::UnsignedByte;
	}

	GrayImage::GrayImage(const GrayImage& image)
		: Image(image)
	{}

	GrayImage& GrayImage::operator= (const GrayImage& image)
	{
		Image::operator= (image);
		return *this;
	}
}
PUNK_ENGINE_END
