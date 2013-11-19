#include "opengl/common/extensions.h"
#include "opengl/common/error/module.h"
#include "vbo.h"

namespace Gpu
{
	namespace OpenGL
	{
		VertexBufferObject::VertexBufferObject() 
			: m_index(0)
			, m_size(0)
		{}

		VertexBufferObject::~VertexBufferObject()
		{
			try
			{
				Destroy();
			}
			catch(...)
			{}
		}

		void VertexBufferObject::Create(const void* data, size_t size)
		{
			if (IsValid())
				Destroy();

            GL_CALL(glGenBuffers(1, &m_index));
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			m_size = size;
		}

		void VertexBufferObject::Destroy()
		{
			if (m_index)
			{
                GL_CALL(glDeleteBuffers(1, &m_index));
                m_index = 0;
			}
		}

		bool VertexBufferObject::IsValid() const
		{
			return m_index != 0;
		}

		void VertexBufferObject::Bind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");

            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
		}

		void VertexBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}


		void* VertexBufferObject::Map()
		{
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
			Unbind();
			return buffer;
		}

		const void* VertexBufferObject::Map() const
		{
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_BUFFER));
			Unbind();
			return buffer;			
		}

		void VertexBufferObject::Unmap() const
		{
			Bind();
            GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
			Unbind();
		}

		void VertexBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"Vertex buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
            GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
			Unbind();
		}
	}
}
