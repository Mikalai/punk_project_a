#ifndef _H_IIMAGE
#define _H_IIMAGE

#include <config.h>
#include <core/iobject.h>
#include <images/formats.h>
#include <images/types.h>
#include "pixel.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	DECLARE_PUNK_GUID(IID_IImage, "684539A7-15BE-418B-AC27-9D440025DCBB");
	DECLARE_PUNK_GUID(IID_IRgbaImage, "F573F681-AEC3-4A2E-A2FF-13E8384A7C59");
	DECLARE_PUNK_GUID(IID_IRgbImage, "4EF78B7E-C73F-49C8-8F44-75E1F419139C");
	DECLARE_PUNK_GUID(IID_IAlphaImage, "97E04AD8-4E4A-4256-855C-5812752591F4");

	DECLARE_PUNK_GUID(CLSID_RgbaImage, "1B9D31B0-518C-4CCB-A36C-14AAB3D45294");
	DECLARE_PUNK_GUID(CLSID_RgbImage, "EC10AB29-6DB8-47C3-BA0D-9CF3FB512D44");
	DECLARE_PUNK_GUID(CLSID_AlphaImage, "9F52CAAE-FB97-4490-9232-670BF8C647CA");

	class IImage : public Core::IObject {
	public:
		virtual std::uint32_t GetWidth() const = 0;
		virtual std::uint32_t GetHeight() const = 0;
		virtual ImageFormat GetFormat() const = 0;
		virtual void SetSize(std::uint32_t width, std::uint32_t height) = 0;
		virtual const void* GetData() const = 0;
		virtual void* GetData() = 0;
	};

	using IImagePointer = Core::Pointer < IImage > ;

	template<ImageFormat format>
	class ImageAccessor
	{
	public:

		ImageAccessor(IImage* image)
			: m_image{ image } {}

		IImage* GetImage() {
			return m_image;
		}

		Pixel<format> GetPixel(std::uint32_t x, std::uint32_t y) {
			std::uint32_t offset = (x + y * m_image->GetWidth()) * Pixel<format>::GetSize();
            void* address = (void*)((std::uint32_t*)m_image->GetData() + offset);
			return Pixel<format>(address);
		}

		std::uint32_t GetSize() const {
			std::uint32_t result = m_image->GetHeight() * m_image->GetHeight() * Pixel<format>::GetSize();
			return result;
		}

	private:
		IImage* m_image;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IIMAGE
