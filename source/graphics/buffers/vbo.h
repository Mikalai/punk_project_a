#ifndef _H_PUNK_OPENGL_BUFFER
#define _H_PUNK_OPENGL_BUFFER

#include <graphics/opengl/module.h>
#include <graphics/primitives/vertex.h>
#include <graphics/error/module.h>
//#include <graphics/primitives/gl_primitive/gl_attribute_configer.h>
#include "ibufffer_object.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

		class VideoMemory;

		template<typename V>
        class PUNK_ENGINE_LOCAL VertexBufferObject : public IBufferObject
		{
		public:
			using CurrentVertex = V;
		public:

			VertexBufferObject(){};

			void QueryInterface(const Core::Guid& type, void** object) {
				Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IBufferObject });
			}

			std::uint32_t AddRef() {
				return m_ref_count.fetch_add(1);
			}

			std::uint32_t Release() {
				auto v = m_ref_count.fetch_sub(1) - 1;
				if (!v) {
					delete this;
				}
				return v;
			}

			//	Only VideoMemory can create it
			virtual ~VertexBufferObject() {
				try {
					Destroy();
				}
				catch (...)
				{
				}
			}
		
			void Create(const CurrentVertex* data, std::uint32_t count) {
                Create((void*)data, count*sizeof(Vertex<CurrentVertex>));
			}

			void Destroy() override {
				if (m_index) {
					GL_CALL(glDeleteBuffers(1, &m_index));
					m_index = 0;
				}
			}

			void Bind() const override {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");

				GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
			}

			void Unbind() const override {
				if (!IsValid())
					throw Error::OpenGLInvalidValueException(L"Buffer is not valid");
				GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
			}
			
			CurrentVertex* MapVB() {
				void* data = Map();
				return (CurrentVertex*)data;
			}

			const CurrentVertex* MapVB() const {
				const void* data = Map();
				return (CurrentVertex*)data;
			}

			void Unmap() const override {
				Bind();
				GL_CALL(glUnmapBuffer(GL_ARRAY_BUFFER));
				Unbind();
			}

			void CopyData(const CurrentVertex* data, std::uint32_t count) {
				CopyData((void*)data, count*sizeof(CurrentVertex));
			}

			bool IsValid() const override{
				return m_index != 0;
			}

			std::uint32_t GetVertexCount() {
				return m_size / sizeof(CurrentVertex);
			}

			std::uint32_t GetSize() override {
				return m_size;
			}
					
		private:					

			void Create(const void* data, std::uint32_t size) override {
				if (IsValid())
					Destroy();

				GL_CALL(glGenBuffers(1, &m_index));
				GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_index));
				GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
				GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
				m_size = size;
			}

			void* Map() override {
				Bind();
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
				Unbind();
				return buffer;
			}

			const void* Map() const override {
				Bind();
				GL_CALL(GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
				Unbind();
				return buffer;
			}

			void CopyData(const void* data, std::uint32_t size) {
				if (m_index == 0) {
					Create(data, size);
				}
				else {
					if (m_size < size)
						throw Error::OpenGLOutOfMemoryException(Core::String(L"Vertex buffer is to small {0} to hold {1}").arg(m_size).arg(size));
					Bind();
					GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
					Unbind();
				}
			}			

			GLuint m_index{ 0 };
			std::uint32_t m_size{ 0 };

			VertexBufferObject(const VertexBufferObject&) = delete;
			VertexBufferObject& operator = (const VertexBufferObject&) = delete;

			std::atomic<std::uint32_t> m_ref_count{ 0 };
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_BUFFER
