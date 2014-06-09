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

		template<class T>
        class PUNK_ENGINE_LOCAL PixelBufferObject : public IBufferObject
        {
        public:

			void QueryInterface(const Core::Guid& type, void** object) {
				Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IBufferObject });
			}

			virtual ~PixelBufferObject() {
				try
				{
					Destroy();
				}
				catch (...)
				{
				}
			}

			void Create(const T* data, std::uint32_t pixels_count) {
				Create(data, sizeof(T)*pixels_count);
			}

			void Destroy() override        {
				if (m_index)
				{
					GL_CALL(glDeleteBuffers(1, &m_index));
					m_index = 0;
				}
			}

			void Bind() const override        {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");

				GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index));
			}

			void Unbind() const override        {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");
				GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
			}

			T* MapPB() {
				return (T*)Map();
			}

			const void* MapPB() const {
				return (const T*)Map();
			}

			void Unmap() const
			{
				Bind();
				GL_CALL(glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER));
				Unbind();
			}

			void CopyData(const T* data, std::uint32_t pixels_count) {
				CopyData((void*)data, sizeof(T)*pixels_count);
			}

			bool IsValid() const override        {
				return m_index != 0;
			}

			std::uint32_t GetSize() {
				return m_size;
			}

		private:
			void Create(const void* data, std::uint32_t size) override   {
				if (IsValid())
					Destroy();

				GL_CALL(glGenBuffers(1, &m_index));
				GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index));
				GL_CALL(glBufferData(GL_PIXEL_UNPACK_BUFFER, size, data, GL_STATIC_DRAW));
				GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
				m_size = size;
			}

			void* Map()
			{
				Bind();
				GL_CALL(glBufferData(GL_PIXEL_UNPACK_BUFFER, m_size, 0, GL_STREAM_DRAW));
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE));
				Unbind();
				return buffer;
			}

			const void* Map() const
			{
				Bind();
				GL_CALL(glBufferData(GL_PIXEL_UNPACK_BUFFER, m_size, 0, GL_STREAM_DRAW));
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE));
				Unbind();
				return buffer;
			}

			void CopyData(const void* data, std::uint32_t size)
			{
				if (m_size < (int)size)
					throw Error::OpenGLOutOfMemoryException(L"pixel buffer is to small " + Core::String::Convert(m_size) + L" to hold " + Core::String::Convert(size));
				Bind();
				GL_CALL(glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, size, data));
				Unbind();
			}

		private:
			GLuint m_index{ 0 };
			GLsizei m_size{ 0 };

			PUNK_OBJECT_DEFAULT_IMPL(PixelBufferObject<T>)
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT
