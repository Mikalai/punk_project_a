//#include <algorithm>
//#include <string>
//#include "string/string.h"
//#include "images/error/module.h"
//#include "importer.h"
//#include "importer_impl.h"
//#include "images/internal_images/rgba_image.h"
//#include "images/internal_images/rgb_image.h"
//#include "images/internal_images/gray_image.h"
//#include "images/internal_images/image_impl.h"
//#include "system/logger/module.h"
//#include "png_importer.h"
//#include "jpg_importer.h"
//#include "tiff_importer.h"
//
//PUNK_ENGINE_BEGIN
//namespace ImageModule
//{
//	Importer::Importer()
//		: Image()
//	{}
//
//    Image* Importer::LoadAnyImage(const Core::String& filename)
//	{
//		if (Load(filename))
//		{
//			Image* image = new Image();
//			std::swap(image->impl_image, impl_image);
//
//			return image;
//		}
//		return nullptr;
//	}
//
//    RGBAImage* Importer::LoadRGBA(const Core::String& filename)
//	{
//		Load(filename);
//        if (impl_image->m_channels != 4)
//            throw Error::ImageException(Core::String("{0} is not an RGBA image").arg(filename));
//		RGBAImage* rgba_image = new RGBAImage;
//		std::swap(rgba_image->impl_image, impl_image);
//		return rgba_image;
//	}
//
//    RGBImage* Importer::LoadRGB(const Core::String& filename)
//	{
//		Load(filename);
//        if (impl_image->m_channels != 3)
//            throw Error::ImageException(Core::String("{0} is not an RGB image").arg(filename));
//		RGBImage* rgb_image = new RGBImage;
//		std::swap(rgb_image->impl_image, impl_image);
//		return rgb_image;
//	}
//
//    GrayImage* Importer::LoadGray(const Core::String& filename)
//	{
//		Load(filename);
//        if (impl_image->m_channels != 1)
//            throw Error::ImageException(Core::String("{0} is not an Alpha image").arg(filename));
//		GrayImage* gray_image = new GrayImage;
//		std::swap(gray_image->impl_image, impl_image);
//		return gray_image;
//	}
//
//    bool Importer::Load(const Core::String& filename)
//	{
//        auto file = filename.ToLower();
//        if (file.EndWith(".png"))
//		{
//			PngImporter importer;
//			importer.Load(filename);
//			std::swap(impl_image, importer.impl_image);
//			return true;
//		}		
//        else if (file.EndWith(".jpeg") || file.EndWith(".jpg"))
//		{
//			JpgImporter importer;
//			importer.Load(filename);
//			std::swap(impl_image, importer.impl_image);
//			return true;
//		}
//        else if (file.EndWith(".tiff") || file.EndWith(".tif"))
//        {
//            TiffImporter importer;
//            importer.Load(filename);
//            std::swap(impl_image, importer.impl_image);
//            return true;
//        }
//		else		
//            throw Error::ImageException("Unsupported file format");
//	}
//}
//PUNK_ENGINE_END
