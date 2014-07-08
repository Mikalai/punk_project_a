#ifdef USE_LIB_TIFF
#include <libtiff/tiffio.h>
#endif
#include <string.h>
#include <system/factory/module.h>
#include <images/error/module.h>
#include <images/iimage.h>
#include <string/module.h>
#include "reader_policy.h"


PUNK_ENGINE_BEGIN
namespace ImageModule
{
	struct PunkTiffHandle
	{
		Core::Buffer* stream;
		Core::String filename;
	};

#ifdef USE_LIB_TIFF
	tmsize_t PunkTIFFReadProc(thandle_t h, void* buffer, tmsize_t size);
	tmsize_t PunkTIFFWriteProc(thandle_t, void*, tmsize_t);
	toff_t PunkTIFFSeekProc(thandle_t h, toff_t offset, int pos);
	int PunkTIFFCloseProc(thandle_t h);
	toff_t PunkTIFFSizeProc(thandle_t h);
	int PunkTIFFMapFileProc(thandle_t, void** base, toff_t* size);
	void PunkTIFFUnmapFileProc(thandle_t, void* base, toff_t size);
#endif

	template<>
	struct ReaderPolicy < ImageFileType::Tiff > {
		
		static bool CanDecode(Core::Buffer& buffer)
		{
			std::uint8_t pattern[] = { 0X49, 0X49 };
			const int bytesToCheck = 2;
			char sig[bytesToCheck];
			buffer.ReadBuffer(sig, bytesToCheck);
			buffer.SetPosition(0);
			if (memcmp(sig, pattern, sizeof(pattern)))
				return false;
			return true;
		}

        static void DecodeBuffer(Core::Buffer& buffer, IImage** _image) {
#ifdef USE_LIB_TIFF
            Core::Pointer<IImage> image {nullptr, Core::DestroyObject};
			PunkTiffHandle h;
			h.stream = &buffer;
			TIFF* tif;
			if (!(tif = TIFFClientOpen("", "r", &h, PunkTIFFReadProc, PunkTIFFWriteProc, PunkTIFFSeekProc, PunkTIFFCloseProc, PunkTIFFSizeProc, PunkTIFFMapFileProc, PunkTIFFUnmapFileProc)))
			{
				throw Error::ImageException("Can't open image file");
			}

			uint32 width;
			uint32 height;
			uint32 bps;
			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);           // uint32 width;
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);        // uint32 height;
			TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);        // uint32 height;

			uint32 npixels = width * height;
			uint32* raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32));

			if (!TIFFReadRGBAImage(tif, width, height, raster, 0))
			{
				_TIFFfree(raster);
				throw Error::ImageException("Failed ro read RGBA image");
			}

            image = System::CreateInstancePtr<IImage>(IID_IRgbaImage);
            image->SetSize(width, height);
            memcpy(image->GetData(), raster, npixels*sizeof(uint32));

			_TIFFfree(raster);

			TIFFClose(tif);
            *_image = image.release();
#else
			return false;
#endif
		}
	};

#ifdef USE_LIB_TIFF
	tmsize_t PunkTIFFReadProc(thandle_t h, void* buffer, tmsize_t size)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		handle->stream->ReadBuffer((char*)buffer, (std::uint32_t)size);
		return size;
		return 0;
	}

	tmsize_t PunkTIFFWriteProc(thandle_t, void*, tmsize_t)
	{
		return 0;
	}

	toff_t PunkTIFFSeekProc(thandle_t h, toff_t offset, int pos)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		handle->stream->SetOffset((std::uint32_t)offset, (int)pos);
		return offset;
		return 0;
	}

	int PunkTIFFCloseProc(thandle_t h)
	{
		return 1;
	}

	toff_t PunkTIFFSizeProc(thandle_t h)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		return handle->stream->GetSize();
	}

	int PunkTIFFMapFileProc(thandle_t, void** base, toff_t* size)
	{
		return 0;
	}

	void PunkTIFFUnmapFileProc(thandle_t, void* base, toff_t size) {
	}

#endif
}
PUNK_ENGINE_END

