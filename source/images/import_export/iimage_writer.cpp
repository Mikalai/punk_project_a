#include <cstdint>
#include <system/filesystem/module.h>
#include <images/iimage.h>
#include <images/iimage_writer.h>
#include "image_file_types.h"
#include "png_reader.h"
#include "tiff_importer.h"

PUNK_ENGINE_BEGIN
namespace ImageModule {

	class ImageWriter : public IImageWriter {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			if (type == Core::IID_IObject) {
				*object = (IImageWriter*)this;
				AddRef();
			}
			else if (type == IID_IImageWriter) {
				*object = (IImageWriter*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IImageWriter
		void Write(IImage* image, Core::Buffer& buffer) override {

		}

		void Write(IImage* image, const Core::String& name, ImageFileType encoding) override {
			Core::Buffer buffer;
			Write(image, buffer, encoding);
			System::BinaryFile::Save(name, buffer);
		}

		void Write(IImage* image, Core::Buffer& buffer, ImageFileType type) {
			if (type == ImageFileType::Png) {
				ImageTypePolicy<ImageFileType::Png>::EncodeBuffer(buffer, image);
			}
			else if (type == ImageFileType::Tiff) {
				ImageTypePolicy<ImageFileType::Tiff>::EncodeBuffer(buffer, image);
			}
		}
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

	PUNK_REGISTER_CREATOR(CLSID_ImageWriter, (System::CreateInstance<ImageWriter, IImageWriter>));
}
PUNK_ENGINE_END
