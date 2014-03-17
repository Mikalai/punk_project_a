#ifndef _H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT
#define _H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT

#include <graphics/opengl/module.h>
#include "ibufffer_object.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		class VideoMemory;

        class PUNK_ENGINE_LOCAL PixelBufferObject : public IBufferObject
        {
        public:
            //	Only VideoMemory can create it
            PixelBufferObject();
            virtual ~PixelBufferObject();
            PixelBufferObject(const PixelBufferObject&) = delete;
            PixelBufferObject& operator = (const PixelBufferObject&) = delete;

            void Create(const void* data, std::uint32_t m_size) override;
            void Destroy() override;
            void Bind() const override;
            void Unbind() const override;
            void* Map() override;
            const void* Map() const override;
            void Unmap() const override;
            void CopyData(const void* data, std::uint32_t size) override;
            bool IsValid() const override;
            std::uint32_t GetSize() override;

		private:					
            GLuint m_index;
            GLsizei m_size;
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT
