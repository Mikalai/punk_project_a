//#ifndef _H_PUNK_IMAGE_IMAGE_PUNK_ENGINE_PUBLIC_IMPL
//#define _H_PUNK_IMAGE_IMAGE_PUNK_ENGINE_PUBLIC_IMPL
//
//#include <ostream>
//#include <istream>
//#include <vector>
//
//#include "images/error/module.h"
//#include "images/formats.h"
//#include "images/import_export/png_importer.h"
//#include "images/import_export/jpg_importer.h"
//#include "string/buffer.h"
//#include "component.h"
//
//PUNK_ENGINE_BEGIN
//namespace ImageModule
//{
//	struct ImageImpl
//	{
//		unsigned m_width;
//		unsigned m_height;
//        unsigned m_channels;
//        ComponentType m_component_type;
//		unsigned m_size;	        
//		ImageFormat m_format;        
//        std::vector<unsigned char> m_data;
//
////		ImageImpl()
////			: m_width(0)
////			, m_height(0)
////            , m_channels(0)
////			, m_size(0)
////			, m_bit_depth(0)
////			, m_format(IMAGE_FORMAT_BAD)
////            , m_data()
////		{}
//
//		ImageImpl(const ImageImpl& impl)
//			: m_width(impl.m_width)
//			, m_height(impl.m_height)
//            , m_channels(impl.m_channels)
//			, m_size(impl.m_size)			
//			, m_format(impl.m_format)
//            , m_component_type(impl.m_component_type)
//            , m_data(impl.m_data.begin(), impl.m_data.end())
//		{}
//
//        ImageImpl(int width, int height, int channels, ComponentType type, ImageFormat format)
//			: m_width(width)
//			, m_height(height)
//            , m_channels(channels)
//            , m_component_type(type)
//            , m_size(m_width*m_height*m_channels*GetComponentSize(type))
//            , m_format(format)
//            , m_data(m_size)
//		{
//			std::fill(m_data.begin(), m_data.end(), 0);
//		}
//
//		~ImageImpl()
//		{}
//
////        void Create(int w, int h, int c, ComponentType type)
////		{
////			m_width = w;
////			m_height = h;
////            m_channels = c;
////            m_component_type = type;
////            m_size = m_width*m_height*m_channels*GetComponentSize(type);
////			m_data.resize(m_size);
////			//m_bit_depth override;
////			//m_format = IMAGE_FORMAT_BAD;
////			std::fill(m_data.begin(), m_data.end(), 0);
////		}
//
//		void Clear()
//		{}		
//
//        void PutLine(int y, unsigned width_in_pixel, unsigned components_per_pixel, void* data)
//		{
//            throw Error::ImageException("Not implemented");
////			if (!m_data.empty())
////				throw ImageException(L"Data is not allocated");
////			if (width_in_pixel != m_width)
////				throw ImageException(L"Impossible to copy line due to different width");
////            if (components_per_pixel != m_channels)
////				throw ImageException(L"Line3D components per pixel count differs from image");
//
////            std::copy(data, data + width_in_pixel*components_per_pixel*GetComponentSize(m_component_type), m_data.begin() + y*m_width*m_channels*GetComponentSize(m_component_type));
//		}
//
//        void Save(Core::Buffer* buffer) const
//		{
//            buffer->WriteUnsigned32(m_width);
//            buffer->WriteUnsigned32(m_height);
//            buffer->WriteUnsigned32(m_channels);
//            buffer->WriteUnsigned32(m_size);
//            buffer->WriteBuffer(&m_data[0], m_size);
//		}
//
//        void Load(Core::Buffer* buffer)
//		{			
//            m_width = buffer->ReadSigned32();
//            m_height = buffer->ReadSigned32();
//            m_channels = buffer->ReadSigned32();
//            m_size = buffer->ReadSigned32();
//            m_data.resize(m_size);
//            buffer->ReadBuffer(&m_data[0], m_size);
//		}
//
//
////		void SetFormat(int format)
////		{
////			m_format = (ImageFormat)format;
////		}
//
////		void SetNumChannels(int channels)
////		{
////            m_channels = channels;
////		}
//
////		void SetDepth(int bpp)
////		{
////			m_bit_depth = bpp;
////		}
//
//        unsigned GetBitDepth() const
//        {
//            unsigned result = m_channels * GetComponentSize(m_component_type) * 8;
//            return result;
//        }
//
//        const void* At(unsigned x, unsigned y, unsigned component) const
//		{
//            size_t index = ((y*m_width+x)*m_channels + component)*GetComponentSize(m_component_type);
//            return (void*)(&m_data[index]);
//        }
//
//        void* At(unsigned x, unsigned y, unsigned component)
//		{
//            return const_cast<void*>(static_cast<const ImageImpl&>(*this).At(x, y, component));
//		}
//
//        void Copy(unsigned x, unsigned y, unsigned component, const void* value)
//        {
//            void* pos = At(x, y, component);
//            switch(m_component_type)
//            {
//            case ComponentType::SignedByte:
//            case ComponentType::UnsignedByte:
//                *(char*)pos = *(const char*)value;
//                break;
//            case ComponentType::Float:
//                *(float*)pos = *(const float*)value;
//                break;
//            default:
//                throw Error::ImageException(L"Can't copy sub image, becuse component type is not supported");
//            }
//        }
//
//		void SetSubImage(unsigned x, unsigned y, const ImageImpl& impl)
//		{
//            if (m_channels != impl.m_channels)
//                throw Error::ImageException(L"Can't set sub image due to different components number");
//
//            if (m_component_type != impl.m_component_type)
//                throw Error::ImageException(L"Can't set sub image due to different components type");
//
//            for (unsigned y_dst = y, y_org = 0; y_dst < m_height && y_org < impl.m_height; ++y_dst, ++y_org)
//			{
//                for (unsigned x_dst = x, x_org = 0; x_dst < m_width && x_org < impl.m_width; ++x_dst, ++x_org)
//				{
//                    for (unsigned c = 0; c < m_channels; ++c)
//					{
//                        Copy(x_dst, y_dst, c, impl.At(x_org, y_org, c));
//					}
//				}
//			}
//		}
//	};
//}
//PUNK_ENGINE_END
//
//#endif
