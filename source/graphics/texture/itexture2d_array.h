#ifndef TEXTURE2D_ARRAY_H
#define TEXTURE2D_ARRAY_H

#include <memory>
#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVideoDriver;

	DECLARE_PUNK_GUID(IID_ITexture2DArray, "48837413-FFC4-4615-AF05-EA9DBC9FA2F8");

    class ITexture2DArray : public ITexture {
	public:
		virtual void Inititalize(std::uint32_t width,
			std::uint32_t height,
			std::uint32_t size,
			ImageModule::ImageFormat internal_format,
			ImageModule::ImageFormat format,
			ImageModule::DataType type,
			const void* data,
			bool use_mipmaps,
			IVideoDriver* driver) = 0;
	};

	using ITexture2DArrayUniquePtr = Core::UniquePtr < ITexture2DArray > ;
}
PUNK_ENGINE_END

#endif // TEXTURE2D_ARRAY_H
