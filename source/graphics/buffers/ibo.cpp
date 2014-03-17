#include <graphics/opengl/module.h>
#include "ibo.h"

PUNK_ENGINE_BEGIN
namespace Graphics
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

        void IndexBufferObject::Create(const void* data, std::uint32_t size)
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

        void IndexBufferObject::CopyData(const void* data, std::uint32_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"Index buffer is to small " + Core::String::Convert(m_size) + L" to hold " + Core::String::Convert(size));
			Bind();
            GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data));
			Unbind();
		}

        std::uint32_t IndexBufferObject::GetSize() {
            return m_size;
        }
	}
    namespace Constructor {
        extern "C" PUNK_ENGINE_API IBufferObject* CreateIndexBuffer(IVideoMemory* memory) {
            return new OpenGL::IndexBufferObject();
        }

        extern "C" PUNK_ENGINE_API void DestroyIndexBuffer(IBufferObject* buffer) {
            OpenGL::IndexBufferObject* object = dynamic_cast<OpenGL::IndexBufferObject*>(buffer);
            delete object;
        }
    }
}
PUNK_ENGINE_END
