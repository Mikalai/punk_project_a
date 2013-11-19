#ifndef _H_PUNK_OPENGL_INDEX_BUFFER
#define _H_PUNK_OPENGL_INDEX_BUFFER

#include "../../../../../config.h"
#include "../../gl/glcorearb.h"

namespace Gpu
{
	namespace OpenGL
	{
		class VideoMemory;

        class PUNK_ENGINE_LOCAL IndexBufferObject
		{
		public:
			
            void Create(const void* data, size_t m_size);
            void Destroy();

            void Bind() const;
            void Unbind() const;

            void* Map();
            const void* Map() const;
            void Unmap() const;

            void CopyData(const void* data, size_t size);

            bool IsValid() const;

            GLsizei GetSize() const { return m_size; }

		private:		

			//	Only VideoMemory can create it
            IndexBufferObject();
            ~IndexBufferObject();

            IndexBufferObject(const IndexBufferObject&);
            IndexBufferObject& operator = (const IndexBufferObject&);
			
            GLuint m_index;
            GLsizei m_size;

			friend class VideoMemory;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_INDEX_BUFFER
