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
			ReaderPolicy<Type>::DecodeBuffer(buffer, &image);
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
			if (ReaderPolicy<ImageFileType::Png>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Png>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Bmp>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Bmp>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Gif>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Gif>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Jpeg>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Jpeg>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Png>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Png>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Tga>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Tga>::DecodeBuffer(buffer, &image);
			else if (ReaderPolicy<ImageFileType::Tiff>::CanDecode(buffer))
				ReaderPolicy<ImageFileType::Tiff>::DecodeBuffer(buffer, &image);
			return image;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

    PUNK_REGISTER_CREATOR(IID_IImageReader, (System::CreateInstance<AnyImageReader, IImageReader>));
}
PUNK_ENGINE_END
