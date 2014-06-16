#ifndef _H_PUNK_OPENGL_INDEX_BUFFER
#define _H_PUNK_OPENGL_INDEX_BUFFER

#include <graphics/opengl/module.h>
#include "ibufffer_object.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

		class VideoMemory;
		
		template<class T>
        class PUNK_ENGINE_LOCAL IndexBufferObject : public IBufferObject {
		public:
			using CurrentIndex = T;
        public:
            //	Only VideoMemory can create it
			virtual ~IndexBufferObject() {
				try
				{
					Destroy();
				}
				catch (...)
				{
				}

			}

			void QueryInterface(const Core::Guid& type, void** object) override {
				Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IBufferObject });
			}

			IndexBufferObject(){};

            IndexBufferObject(const IndexBufferObject&) = delete;
            IndexBufferObject& operator = (const IndexBufferObject&) = delete;

			void Create(const T* data, std::uint32_t count) {
				Create(data, sizeof(T)*count);
			}

			void Destroy() override {
						if (m_index)
						{
							GL_CALL(glDeleteBuffers(1, &m_index));
							m_index = 0;
						}
			}

			void Bind() const override {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");

				GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index));
			}

			void Unbind() const override {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");
				GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			}
			T* MapIB() {
				return (T*)Map();
			}

			const T* MapIB() const {
				return (const T*)Map();
			}

			void Unmap() const override {
				Bind();
				GL_CALL(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
				Unbind();
			}
            
			void CopyData(const T* data, std::uint32_t count) {
				CopyData((void*)data, count*sizeof(T));
			}
			
			bool IsValid() const override		{
				return m_index != 0;
			}

			std::uint32_t GetCount() {
				return m_size / sizeof(T);
			}

			std::uint32_t GetSize() override {
				return m_size;
			}

		private:		

			void Create(const void* data, std::uint32_t size)
			{
				if (IsValid())
					Destroy();

				GL_CALL(glGenBuffers(1, &m_index));
				GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index));
				GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
				GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
				m_size = size;
			}

			void* Map()
			{
				Bind();
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
				Unbind();
				return buffer;
			}

			const void* Map() const
			{
				Bind();
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_BUFFER));
				Unbind();
				return buffer;
			}

			void CopyData(const void* data, std::uint32_t size)
			{
				if (m_index == 0) {
					Create(data, size);
				}
				else {
					if (m_size < (GLsizei)size)
						throw Error::OpenGLOutOfMemoryException(L"Index buffer is to small " + Core::String::Convert(m_size) + L" to hold " + Core::String::Convert(size));
					Bind();
					GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data));
					Unbind();
				}
			}
			
			private:
			GLuint m_index{ 0 };
			GLsizei m_size{ 0 };

			PUNK_OBJECT_DEFAULT_IMPL(IndexBufferObject<T>)
		};

		template<>
		class PUNK_ENGINE_LOCAL IndexBufferObject < std::nullptr_t > {
		public:
			using CurrentIndex = std::nullptr_t;
		};
	}    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_INDEX_BUFFER
