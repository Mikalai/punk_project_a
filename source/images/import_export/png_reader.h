#include <fstream>
#include <istream>
#include <ostream>
#include <stdio.h>
#include <string/module.h>
#include <system/logger/module.h>
#include <system/factory/module.h>
#include <images/iimage.h>
#include "reader_policy.h"

#ifdef USE_LIB_PNG
#include <libpng/png.h>
#endif // USE_LIB_PNG

PUNK_ENGINE_BEGIN
namespace ImageModule
{

#ifdef USE_LIB_PNG
	void read(png_structp png, png_bytep data, png_size_t size);
	void read2(png_structp png, png_bytep data, png_size_t size);
	void write(png_structp png, png_bytep data, png_size_t size);
	void write2(png_structp png, png_bytep data, png_size_t size);
#endif  //  USE_LIB_PNG


	template<>
	struct ImageTypePolicy < ImageFileType::Png > {

		static bool CanDecode(Core::Buffer& buffer)
		{
			const int bytesToCheck = 8;
			char sig[bytesToCheck];
			buffer.ReadBuffer(sig, bytesToCheck);
			buffer.SetPosition(0);
			if (png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck))
				return false;
			return true;
		}

		static void EncodeBuffer(Core::Buffer& buffer, IImage* image) {			

			/* initialize stuff */
			auto png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (!png_ptr) {
				System::GetDefaultLogger()->Error("png_create_write_struct failed");
				return;
			}

			auto info_ptr = png_create_info_struct(png_ptr);
			if (!info_ptr) {
				System::GetDefaultLogger()->Error("png_create_info_struct failed");
				return;
			}

			if (setjmp(png_jmpbuf(png_ptr))) {
				System::GetDefaultLogger()->Error("Error during init_io");
				return;
			}

			png_set_write_fn(png_ptr, &buffer, write2, NULL);

			/* write header */
			if (setjmp(png_jmpbuf(png_ptr))) {
				System::GetDefaultLogger()->Error("Error during writing header");
				return;
			}			

			int color_type = 0;
			if (image->GetFormat() == ImageFormat::RGBA)
				color_type = PNG_COLOR_TYPE_RGBA;
			else if (image->GetFormat() == ImageFormat::RGB)
				color_type = PNG_COLOR_TYPE_RGB;
			else if (image->GetFormat() == ImageFormat::ALPHA)
				color_type = PNG_COLOR_TYPE_GRAY;

			png_set_IHDR(png_ptr, info_ptr, image->GetWidth(), image->GetHeight(),
				GetBitDepth(image->GetFormat()), color_type, PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			png_write_info(png_ptr, info_ptr);


			/* write bytes */
			if (setjmp(png_jmpbuf(png_ptr))) {
				System::GetDefaultLogger()->Error("Error during writing bytes");
				return;
			}

			png_bytep row_pointers[] = { (png_bytep)image->GetData() };
			png_write_image(png_ptr, row_pointers);


			/* end write */
			if (setjmp(png_jmpbuf(png_ptr))) {
				System::GetDefaultLogger()->Error("Error during end of write");
				return;
			}

			png_write_end(png_ptr, NULL);

			///* cleanup heap allocation */
			//for (y = 0; y < height; y++)
			//	free(row_pointers[y]);
			//free(row_pointers);			
		}

		static void DecodeBuffer(Core::Buffer& buffer, IImage** _image) {
#ifdef USE_LIB_PNG
			Core::Pointer<IImage> image{ nullptr, Core::DestroyObject };
			const int bytesToCheck = 8;

			char sig[bytesToCheck];
			buffer.ReadBuffer(sig, bytesToCheck);
			if (png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck))
				throw Error::ImageException(L"It is not a png file");

			png_structp png_ptr;
			png_infop info_ptr;

			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (png_ptr == NULL)
				throw Error::ImageException(L"It is not a png file");

			info_ptr = png_create_info_struct(png_ptr);

			if (info_ptr == NULL)
			{
				png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
				throw Error::ImageException(L"It is not a png file");
			}

			png_infop end_info = png_create_info_struct(png_ptr);
			if (!end_info)
			{
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
				throw Error::ImageException(L"It is not a png file");
			}

			png_set_read_fn(png_ptr, &buffer, read2);
			//png_init_io(png_ptr, );
			png_set_sig_bytes(png_ptr, bytesToCheck);
			png_read_info(png_ptr, info_ptr);

			unsigned width = png_get_image_width(png_ptr, info_ptr);
			unsigned height = png_get_image_height(png_ptr, info_ptr);
			unsigned bpp = png_get_bit_depth(png_ptr, info_ptr);
			int	colorType = png_get_color_type(png_ptr, info_ptr);
			int	rowBytes = (int)png_get_rowbytes(png_ptr, info_ptr);
			unsigned channels = png_get_channels(png_ptr, info_ptr);
			ImageFormat format = ImageFormat::ALPHA;

			switch (colorType)
			{
			case PNG_COLOR_TYPE_RGB:
				image = System::CreateInstancePtr<IImage>(CLSID_RgbImage, IID_IRgbImage);
				format = ImageFormat::RGB;
				break;

			case PNG_COLOR_TYPE_RGB_ALPHA:
				image = System::CreateInstancePtr<IImage>(CLSID_RgbaImage, IID_IRgbaImage);
				format = ImageFormat::RGBA;
				break;

			case PNG_COLOR_TYPE_GRAY:
			case PNG_COLOR_TYPE_GRAY_ALPHA:
				image = System::CreateInstancePtr<IImage>(CLSID_AlphaImage, IID_IAlphaImage);
				format = ImageFormat::ALPHA;
				break;

			case PNG_COLOR_TYPE_PALETTE:
				image = System::CreateInstancePtr<IImage>(CLSID_RgbImage, IID_IRgbImage);
				format = ImageFormat::RGB;
				break;

			default:
				break;
			}

			//		if (colorType == PNG_COLOR_TYPE_PALETTE)
			//			png_set_palette_to_rgb(png_ptr);

			//		if (colorType == PNG_COLOR_TYPE_GRAY && bpp < 8)
			//			png_set_expand_gray_1_2_4_to_8(png_ptr);

			//		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			//			png_set_tRNS_to_alpha(png_ptr);

			if (channels == 0)
			{
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
				throw Error::ImageException(L"Can't load file: ");
			}

			image->SetSize(width, height);

			png_bytep * rowPtr = new png_bytep[height];
			uint32_t     * lineBuf = new uint32_t[width];

			for (unsigned i = 0; i < height; i++)
				rowPtr[i] = (png_bytep)malloc(rowBytes);

			png_read_image(png_ptr, rowPtr);

			unsigned char* offset = (unsigned char*)image->GetData();

			// now rebuild the ImageFile
			for (int i = 0; i < (int)height; i++)
			{
				png_bytep	ptr = rowPtr[i];

				if (colorType == PNG_COLOR_TYPE_RGB)
				{
					for (unsigned x = 0; x < width; x++, ptr += 3)
						lineBuf[x] = ptr[2] << 16 | ptr[1] << 8 | ptr[0];
				}
				else if (colorType == PNG_COLOR_TYPE_RGB_ALPHA)
				{
					for (unsigned x = 0; x < width; x++, ptr += 4)
						lineBuf[x] = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
				}
				else if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY)
				{
					for (unsigned x = 0; x < width; x++, ptr += 1)
						lineBuf[x] = ptr[0];
				}
				else if (colorType == PNG_COLOR_TYPE_PALETTE)
				{
					png_color * pngPal = NULL;
					png_color   pal[256];
					int			numColors;
					int			numEntries = (1 << bpp) - 1;

					if (!png_get_PLTE(png_ptr, info_ptr, (png_colorp *)&pngPal, &numColors))
					{
						// This is a grayscale ImageFile, build a grayscale palette
						numColors = numEntries + 1;
						pngPal = pal;

						for (int z = 0; z < numColors; z++)
							pngPal[z].red =
							pngPal[z].green =
							pngPal[z].blue = (z * 255) / numEntries;
					}
					else
					{
						for (int z = 0; z < numColors; z++)
						{
							pngPal[z].red = (pngPal[z].red * 255) / numEntries;
							pngPal[z].green = (pngPal[z].green * 255) / numEntries;
							pngPal[z].blue = (pngPal[z].blue * 255) / numEntries;
						}
					}

					for (int z = 0; z < (int)width; z++)
					{
						int	ind = ptr[z];

						lineBuf[z] = pngPal[ind].red | pngPal[ind].green << 8 | pngPal[ind].blue << 16;
					}
				}
				else
				{
					for (unsigned x = 0; x < width; x++, ptr++)
						lineBuf[x] = ptr[0];
				}

				unsigned char* src = (unsigned char*)lineBuf;
				unsigned char* offset = (unsigned char*)image->GetData() + height*width*channels - (i + 1)*width*channels;	//alligned
				for (int k = 0; k < (int)width; k++, src += 4)
				{
					if (channels == 1)
					{
						*offset++ = src[0];
					}
					else if (channels == 3)
					{
						*offset++ = src[0];
						*offset++ = src[1];
						*offset++ = src[2];
						//*offset++ = 0xFF;
					}
					else
					{
						*offset++ = src[0];
						*offset++ = src[1];
						*offset++ = src[2];
						*offset++ = src[3];
					}
				}

				free(rowPtr[i]);
			}

			delete[] lineBuf;
			delete[] rowPtr;

			png_read_end(png_ptr, end_info);
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

			*_image = image.release();
#else   //  USE_LIB_PNG
			(void)stream; (void)image;
			throw System::PunkNotImplemented(L"Can't import png, because png lib was not included in the project");
#endif  //  USE_LIB_PNG

		}
	};

#ifdef USE_LIB_PNG
	inline void read(png_structp png, png_bytep data, png_size_t size)
	{
		std::istream& stream = *(std::istream*)(png_get_io_ptr(png));
		stream.read((char*)data, size);
	}

	inline void read2(png_structp png, png_bytep data, png_size_t size)
	{
		Core::Buffer* buffer = (Core::Buffer*)(png_get_io_ptr(png));
		buffer->ReadBuffer(data, (std::uint32_t)size);
	}

	inline void write(png_structp png, png_bytep data, png_size_t size)
	{
		std::ostream& stream = *(std::ostream*)(png_get_io_ptr(png));
		stream.write((char*)data, size);
	}

	inline void write2(png_structp png, png_bytep data, png_size_t size)
	{
		Core::Buffer* buffer = (Core::Buffer*)(png_get_io_ptr(png));
		buffer->WriteBuffer(data, (std::uint32_t)size);
	}
#endif  //  USE_LIB_PNG

	//	bool PngImporter::Load(std::istream& stream, Image* image)
	//	{
	//#ifdef USE_LIB_PNG
	//		const int bytesToCheck = 8;
	//
	//		char sig[bytesToCheck];
	//		stream.read(sig, bytesToCheck);
	//        if ( png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck) )
	//            throw Error::ImageException(L"It is not a png file stream");
	//
	//		png_structp png_ptr;
	//		png_infop info_ptr;
	//
	//		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	//
	//		if (png_ptr == NULL)
	//            throw Error::ImageException(L"It is not a png file stream");
	//
	//		info_ptr = png_create_info_struct(png_ptr);
	//
	//        if (info_ptr == NULL) {
	//			png_destroy_read_struct ( &png_ptr, (png_infopp) NULL, (png_infopp)NULL );
	//            throw Error::ImageException(L"It is not a png file stream");
	//		}
	//
	//		png_infop end_info = png_create_info_struct(png_ptr);
	//        if (!end_info) {
	//			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	//            throw Error::ImageException(L"It is not a png file stream");
	//		}
	//
	//		png_set_read_fn(png_ptr, &stream, read);
	//		//png_init_io(png_ptr, );
	//		png_set_sig_bytes(png_ptr, bytesToCheck);
	//		png_read_info(png_ptr, info_ptr);
	//
	//		unsigned width = png_get_image_width(png_ptr, info_ptr);
	//		unsigned height = png_get_image_height(png_ptr, info_ptr);
	//		unsigned bpp = png_get_bit_depth(png_ptr, info_ptr);
	//		int	colorType = png_get_color_type(png_ptr, info_ptr);
	//		int	rowBytes = png_get_rowbytes(png_ptr, info_ptr);
	//		unsigned channels = png_get_channels(png_ptr, info_ptr);
	//        ImageFormat format = ImageFormat::ALPHA;
	//
	//		switch ( colorType )
	//		{
	//		case PNG_COLOR_TYPE_RGB:
	//			//channels = bpp / 8;
	//            format = ImageFormat::RGB;
	//			break;
	//
	//		case PNG_COLOR_TYPE_RGB_ALPHA:
	//			//channels = bpp / 8;
	//			format = ImageFormat::RGBA;
	//			break;
	//
	//		case PNG_COLOR_TYPE_GRAY:
	//		case PNG_COLOR_TYPE_GRAY_ALPHA:
	//			//channels = bpp / 8;
	//            format = ImageFormat::ALPHA;
	//			break;
	//
	//		case PNG_COLOR_TYPE_PALETTE:
	//			channels = 3;
	//            format = ImageFormat::RGB;
	//			break;
	//
	//		default:
	//			break;
	//		}
	//
	////		if (colorType == PNG_COLOR_TYPE_PALETTE)
	////			png_set_palette_to_rgb(png_ptr);
	//
	////		if (colorType == PNG_COLOR_TYPE_GRAY && bpp < 8)
	////			png_set_expand_gray_1_2_4_to_8(png_ptr);
	//
	////		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	////			png_set_tRNS_to_alpha(png_ptr);
	//
	//		if ( channels == 0 )
	//		{
	//			png_destroy_read_struct ( &png_ptr, &info_ptr, (png_infopp) NULL );
	//            throw Error::ImageException(L"Can't load file: ");
	//		}
	//
	//        image->Create(width, height, channels, ComponentType::UnsignedByte, format);
	//
	//		png_bytep * rowPtr  = new png_bytep[height];
	//        uint32_t     * lineBuf = new uint32_t[width];
	//
	//		for (unsigned i = 0; i < height; i++ )
	//			rowPtr [i] = (png_bytep) malloc ( rowBytes );
	//
	//		png_read_image ( png_ptr, rowPtr );
	//
	//        unsigned char* offset = (unsigned char*)image->GetData();
	//
	//		// now rebuild the ImageFile
	//		for (int i = 0; i < (int)height; i++ )
	//		{
	//			png_bytep	ptr = rowPtr [i];
	//
	//			if ( colorType == PNG_COLOR_TYPE_RGB )
	//			{
	//                for ( unsigned x = 0; x < width; x++, ptr += 3 )
	//					lineBuf [x] = ptr[2] << 16 | ptr[1] << 8 | ptr[0];
	//			}
	//			else if ( colorType == PNG_COLOR_TYPE_RGB_ALPHA )
	//			{
	//                for ( unsigned x = 0; x < width; x++, ptr += 4 )
	//					lineBuf [x] = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
	//			}
	//			else if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY)
	//			{
	//                for ( unsigned x = 0; x < width; x++, ptr += 1)
	//					lineBuf [x] = ptr[0];
	//			}
	//			else if ( colorType == PNG_COLOR_TYPE_PALETTE )
	//			{
	//				png_color * pngPal = NULL;
	//				png_color   pal [256];
	//				int			numColors;
	//				int			numEntries = (1 << bpp) - 1;
	//
	//				if (!png_get_PLTE ( png_ptr, info_ptr, (png_colorp *)&pngPal, &numColors ) )
	//				{
	//					// This is a grayscale ImageFile, build a grayscale palette
	//					numColors = numEntries + 1;
	//					pngPal    = pal;
	//
	//                    for (int z = 0; z < numColors; z++)
	//						pngPal [z].red   =
	//						pngPal [z].green =
	//						pngPal [z].blue  = (z * 255) / numEntries;
	//				}
	//				else
	//				{
	//                    for (int z = 0; z < numColors; z++ )
	//					{
	//						pngPal [z].red   = (pngPal [z].red   * 255) / numEntries;
	//						pngPal [z].green = (pngPal [z].green * 255) / numEntries;
	//						pngPal [z].blue  = (pngPal [z].blue  * 255) / numEntries;
	//					}
	//				}
	//
	//                for (int z = 0; z < (int)width; z++ )
	//				{
	//					int	ind = ptr [z];
	//
	//					lineBuf [z] = pngPal[ind].red | pngPal[ind].green << 8 | pngPal[ind].blue << 16;
	//				}
	//			}
	//			else
	//			{
	//                for ( unsigned x = 0; x < width; x++, ptr++ )
	//					lineBuf [x] = ptr [0];
	//			}
	//
	//			unsigned char* src = (unsigned char*)lineBuf;
	//            unsigned char* offset = (unsigned char*)image->GetData() + height*width*channels - (i+1)*width*channels;	//alligned
	//            for (int k = 0; k < (int)width; k++, src += 4)
	//			{
	//				if (channels == 1)
	//				{
	//					*offset++ = src[0];
	//				}
	//				else if (channels == 3)
	//				{
	//					*offset++ = src[0];
	//					*offset++ = src[1];
	//					*offset++ = src[2];
	//					//*offset++ = 0xFF;
	//				}
	//				else
	//				{
	//					*offset++ = src[0];
	//					*offset++ = src[1];
	//					*offset++ = src[2];
	//					*offset++ = src[3];
	//				}
	//			}
	//
	//			free ( rowPtr [i] );
	//		}
	//
	//		delete[] lineBuf;
	//		delete[] rowPtr;
	//
	//		png_read_end            ( png_ptr, end_info );
	//		png_destroy_read_struct ( &png_ptr, &info_ptr, &end_info );
	//
	//		return true;
	//#else   //  USE_LIB_PNG
	//        (void)stream; (void)image;
	//        throw System::PunkNotImplemented(L"Can't import png, because png lib was not included in the project");
	//#endif  //  USE_LIB_PNG
	//	}

	//   bool PngImporter::Load(const Core::String& file)
	//{
	//       std::ifstream stream((char*)file.ToUtf8().Data(), std::ios_base::binary);
	//	if (!stream.is_open())
	//           throw Error::ImageException(L"Can't open file: " + file);
	//	Load(stream, this);
	//	stream.close();
	//	return true;
	//}
}
PUNK_ENGINE_END
