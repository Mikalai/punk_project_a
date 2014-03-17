#include <graphics/opengl/module.h>
#include <graphics/error/module.h>
#include "vbo.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

		VertexBufferObject::VertexBufferObject() 
			: m_index(0)
            , m_size(0) {}

        VertexBufferObject::~VertexBufferObject() {
            try {
				Destroy();
			}
			catch(...)
			{}
		}

        void VertexBufferObject::Create(const void* data, std::uint32_t size) {
			if (IsValid())
				Destroy();

            GL_CALL(glGenBuffers(1, &m_index));
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
            GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			m_size = size;
		}

        void VertexBufferObject::Destroy() {
            if (m_index) {
                GL_CALL(glDeleteBuffers(1, &m_index));
                m_index = 0;
			}
		}

        bool VertexBufferObject::IsValid() const {
			return m_index != 0;
		}

        void VertexBufferObject::Bind() const {
			if (!IsValid())
                throw OpenGLInvalidValueException(L"Buffer is not valid");

            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
		}

        void VertexBufferObject::Unbind() const {
			if (!IsValid())
                throw OpenGLInvalidValueException(L"Buffer is not valid");
            GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}


        void* VertexBufferObject::Map() {
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
			Unbind();
			return buffer;
		}

        const void* VertexBufferObject::Map() const {
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_BUFFER));
			Unbind();
			return buffer;			
		}

        void VertexBufferObject::Unmap() const {
			Bind();
            GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
			Unbind();
		}

        void VertexBufferObject::CopyData(const void* data, std::uint32_t size) {
			if (m_size < size)
                throw OpenGLOutOfMemoryException(Core::String(L"Vertex buffer is to small {0} to hold {1}").arg(m_size).arg(size));
			Bind();
            GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
			Unbind();
		}

        std::uint32_t VertexBufferObject::GetSize() {
            return m_size;
        }
	}
    namespace Constructor {
        extern "C" PUNK_ENGINE_API IBufferObject* CreateVertexBuffer(IVideoMemory* memory) {
            return new OpenGL::VertexBufferObject();
        }

        extern "C" PUNK_ENGINE_API void DestroyVertexBuffer(IBufferObject* buffer) {
            OpenGL::VertexBufferObject* object = dynamic_cast<OpenGL::VertexBufferObject*>(buffer);
            delete object;
        }
    }
}
PUNK_ENGINE_END
