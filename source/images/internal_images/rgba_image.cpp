#include "rgba_image.h"
#include "image_impl.h"

PUNK_ENGINE_BEGIN
namespace Image
{
	RGBAImage::RGBAImage()
		: Image()
	{
        impl_image->m_channels = 4;
		impl_image->m_format = IMAGE_FORMAT_RGBA;
        impl_image->m_component_type = ComponentType::UnsignedByte;
	}

	RGBAImage::RGBAImage(const RGBAImage& image)
		: Image(image)
	{
	}

	RGBAImage& RGBAImage::operator = (const RGBAImage& image)
	{
		Image::operator = (image);
		return *this;
	}
}
PUNK_ENGINE_END
