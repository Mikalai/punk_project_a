#include "../extensions.h"
#include "../error/module.h"
#include "ibo.h"

namespace Gpu
{
	namespace OpenGL
	{
		IndexBufferObject::IndexBufferObject() 
			: m_index(0)
			, m_size(0)
		{}

		IndexBufferObject::~IndexBufferObject()
		{
			try
			{
				Destroy();
			}
			catch(...)
			{}
		}

		void IndexBufferObject::Create(const void* data, size_t size)
		{
			if (IsValid())
				Destroy();

            GL_CALL(glGenBuffers(1, &m_index));
            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index));
            GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			m_size = size;
		}

		void IndexBufferObject::Destroy()
		{
			if (m_index)
			{
                GL_CALL(glDeleteBuffers(1, &m_index));
                m_index = 0;
			}
		}

		bool IndexBufferObject::IsValid() const
		{
			return m_index != 0;
		}

		void IndexBufferObject::Bind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");

            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index));
		}

		void IndexBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}


		void* IndexBufferObject::Map()
		{
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
			Unbind();
			return buffer;
		}

		const void* IndexBufferObject::Map() const
		{
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_BUFFER));
			Unbind();
			return buffer;			
		}

		void IndexBufferObject::Unmap() const
		{
			Bind();
            GL_CALL(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
			Unbind();
		}

		void IndexBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"Index buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
            GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data));
			Unbind();
		}
	}
}
