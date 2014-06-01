#ifndef _H_PUNK_IMAGE_FILE
#define _H_PUNK_IMAGE_FILE

#include "config.h"
#include "formats.h"

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace ImageModule {

	class PUNK_ENGINE_API ImageFile
	{
	protected:
		struct Rep
		{
			unsigned char* m_data;
			unsigned m_width;
			unsigned m_height;
			unsigned m_depth;
			//unsigned m_channels;
			unsigned m_size;
			unsigned m_bpp;
			ImageFormat m_format;
			unsigned m_used_count;

			Rep();
			Rep(const Rep& rep);
			~Rep();
            void SetSize(unsigned width, unsigned height);
			void SetSize(unsigned size);
			Rep* GetOwnCopy();
		};

		Rep* m_rep;

	public:
		
		ImageFile();
		ImageFile(const ImageFile& file);
		ImageFile& operator = (const ImageFile& file);

		virtual ~ImageFile();

        virtual bool Save(const wchar_t*) const { return false; }
        virtual bool Load(const wchar_t*) { return false; }

        virtual void Store(Core::Buffer& buffer);
        virtual void Restore(Core::Buffer& buffer);

		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetChannels() const;

		void SetSize(unsigned width, unsigned height);
		void SetPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void SetFormat(ImageFormat format);
		ImageFormat GetFormat() const;
		const unsigned char* GetPixel(unsigned x, unsigned y) const;

		void* Lock();
		const void* Lock() const;
		void Unlock(void* p);
		void Unlock(const void* p) const;

		
	};
}
PUNK_ENGINE_END
#endif
