#include <system/filesystem/module.h>
#include <images/error/module.h>
#include <images/iimage_reader.h>
#include <images/iimage.h>
#include "image_file_types.h"
#include "reader_policy.h"
#include "png_reader.h"
#include "jpg_reader.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	template<ImageFileType Type>
	class ImageReader {
	public:	

		IImage* Read(Core::Buffer& buffer) {
			IImage* image;
			ImageTypePolicy<Type>::DecodeBuffer(buffer, &image);
			return image;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

	class AnyImageReader : public IImageReader {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IImageReader });
		}

		std::uint32_t AddRef() {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t Release() {
			std::uint32_t v = m_ref_count;
			if (!m_ref_count.fetch_sub(1)) {
				delete this;
			}
			return --v;
		}

		//	IImageReader
		IImage* Read(const Core::String& filename) override {
			Core::Buffer buffer;
			if (!System::BinaryFile::Load(filename, buffer))
				throw Error::ImageException("Can't read " + filename);
			return Read(buffer);
		}

		IImage* Read(Core::Buffer& buffer) {
			IImage* image = nullptr;
			if (ImageTypePolicy<ImageFileType::Png>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Png>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Bmp>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Bmp>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Gif>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Gif>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Jpeg>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Jpeg>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Png>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Png>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Tga>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Tga>::DecodeBuffer(buffer, &image);
			else if (ImageTypePolicy<ImageFileType::Tiff>::CanDecode(buffer))
				ImageTypePolicy<ImageFileType::Tiff>::DecodeBuffer(buffer, &image);
			return image;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

    PUNK_REGISTER_CREATOR(CLSID_ImageReader, (System::CreateInstance<AnyImageReader, IImageReader>));
}
PUNK_ENGINE_END
