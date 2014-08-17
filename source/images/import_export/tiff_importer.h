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
	struct ImageTypePolicy < ImageFileType::Tiff > {

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

		static void GetSampleFormat(ImageFormat format, int* sample_format, int* samples_per_pixel) {
			switch (format)
			{
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::DepthComponent:
				break;
			case Punk::Engine::ImageModule::ImageFormat::DEPTH_COMPONENT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::DEPTH_COMPONENT24:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DEPTH_COMPONENT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE4_ALPHA4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE6_ALPHA2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE8_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE12_ALPHA4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE12_ALPHA12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE16_ALPHA16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R3_G3_B2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB5:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB10:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB5_A1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGB10_A2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA16F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA32F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX4:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX12:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COLOR_INDEX16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_LUMINANCE8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_RGB8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_RGBA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_INTENSITY8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_HILO16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_HILO16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DSDT8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DSDT8_MAG8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_HILO8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SIGNED_HILO8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::FloatR16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::FloatR32:
				*sample_format = SAMPLEFORMAT_IEEEFP;
				*samples_per_pixel = 1;
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RG16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RGB16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RGBA16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RG32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RGB32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_FLOAT_RGBA32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DEPTH24_STENCIL8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::DEPTH_COMPONENT32F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_DEPTH32F_STENCIL8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SRGB8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::SRGB8_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SLUMINANCE8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_SLUMINANCE8_ALPHA8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB9_E5:
				break;
			case Punk::Engine::ImageModule::ImageFormat::R11F_G11F_B10F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RGB8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_ALPHA8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_INTENSITY8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_LUMINANCE_ALPHA8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R32UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R16UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R8UI:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R32I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R16I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R8I:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R8:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R16:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG16F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R16F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_RG32F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_R32F:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_BGRA:
				break;
			case Punk::Engine::ImageModule::ImageFormat::IMAGE_FORMAT_BGR:
				break;
			case Punk::Engine::ImageModule::ImageFormat::ALPHA:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGBA:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RGB:
				break;
			case Punk::Engine::ImageModule::ImageFormat::RED:
				break;
			case Punk::Engine::ImageModule::ImageFormat::BAD:
				break;
			default:
				break;
			}
		}

		static void EncodeBuffer(Core::Buffer& buffer, IImage* image) {
#ifdef USE_LIB_TIFF
			PunkTiffHandle h;
			buffer.SetPosition(0);
			h.stream = &buffer;
			TIFF* tif;
			///tif = TIFFOpen("image_file.tiff", "w");
			if (!(tif = TIFFClientOpen("", "w", &h, PunkTIFFReadProc, PunkTIFFWriteProc, PunkTIFFSeekProc, PunkTIFFCloseProc, PunkTIFFSizeProc, PunkTIFFMapFileProc, PunkTIFFUnmapFileProc)))
			{
				throw Error::ImageException("Can't open image file");
			}

			uint32 width = image->GetWidth();
			uint32 height = image->GetHeight();
			uint16 bps = GetBitDepth(image->GetFormat());
			int samples_per_pixel = 0;
			int sample_format = 0;
			GetSampleFormat(image->GetFormat(), &sample_format, &samples_per_pixel);
			TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);           // uint32 width;
			TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);        // uint32 height;
			TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, samples_per_pixel);
			TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, bps);        // uint32 height;
			TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);        // uint32 height;
			TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
			//TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 1);
			TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, sample_format);
			TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

			uint32 npixels = width * height;
			uint32* raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32));

			for (int i = 0; i < image->GetHeight(); ++i) {
				TIFFWriteScanline(tif, image->GetScanline(i), i);
			}
			TIFFClose(tif);
#else
			return false;
#endif
		}

		static void DecodeBuffer(Core::Buffer& buffer, IImage** _image) {
#ifdef USE_LIB_TIFF
			Core::Pointer<IImage> image{ nullptr, Core::DestroyObject };
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

			image = System::CreateInstancePtr<IImage>(CLSID_RgbaImage, IID_IRgbaImage);
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
	inline tmsize_t PunkTIFFReadProc(thandle_t h, void* buffer, tmsize_t size)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		handle->stream->ReadBuffer((char*)buffer, (std::uint32_t)size);
		return size;
	}

	inline tmsize_t PunkTIFFWriteProc(thandle_t h, void* buffer, tmsize_t size)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		handle->stream->WriteBuffer((char*)buffer, (std::uint32_t)size);
		return size;
	}

	inline toff_t PunkTIFFSeekProc(thandle_t h, toff_t offset, int pos)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		handle->stream->SetOffset((std::uint32_t)offset, (int)pos);
		return handle->stream->GetPosition();
		return 0;
	}

	inline int PunkTIFFCloseProc(thandle_t h)
	{
		return 1;
	}

	inline toff_t PunkTIFFSizeProc(thandle_t h)
	{
		PunkTiffHandle* handle = (PunkTiffHandle*)h;
		return handle->stream->GetSize();
	}

	inline int PunkTIFFMapFileProc(thandle_t, void** base, toff_t* size)
	{
		return 0;
	}

	inline void PunkTIFFUnmapFileProc(thandle_t, void* base, toff_t size) {
	}
#endif
}
PUNK_ENGINE_END

