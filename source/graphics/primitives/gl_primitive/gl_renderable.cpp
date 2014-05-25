//#include "gl_renderable.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//	namespace OpenGL
//	{
//			GlRenderable::GlRenderable(IVideoDriver* driver)
//				: m_driver(driver)
//				, m_index_count(0)
//				, m_vao(0)
//				, m_vertex_size(0)
//				, m_was_modified(true)
//				, m_primitive_count(0)
//				, m_index_buffer(nullptr)
//				, m_vertex_buffer(nullptr)
//			{}
//
//			GlRenderable::~GlRenderable() {
//				Clear();
//			}
//
//			void GlRenderable::Bind(int64_t supported_by_context)
//			{
//				if (m_was_modified)
//				{
//					Cook();
//					m_was_modified = false;
//				}
//				GL_CALL(glBindVertexArray(m_vao));				
//			}
//
//			void GlRenderable::Unbind()
//			{
//				GL_CALL(glBindVertexArray(0));
//				for (int i = 0; i < 16; i++)
//				{
//					GL_CALL(glDisableVertexAttribArray(i));
//				}
//			}
//
//			void SetVertexBuffer(const IVertexArray* vbuffer)
//			{
//				SetVertexBuffer(vbuffer->GetVertexBuffer(), vbuffer->GetMemoryUsage());
//			}
//
//			void Render()
//			{
//				GLenum type = PrimitiveTypeToOpenGL(CurrentPrimitive);
//				int size = sizeof(CurrentIndex);
//				if (size == 4) {
//					GL_CALL(glDrawElements(type, m_index_count, GL_UNSIGNED_INT, 0));
//				}
//				else if (size == 2) {
//					GL_CALL(glDrawElements(type, m_index_count, GL_SHORT, 0));
//				}
//			}
//
//			void SetVertexBuffer(const void* vbuffer, int size_in_bytes)
//			{
//				m_vb_size = size_in_bytes;
//
//				m_vertex_buffer = dynamic_cast<VertexBufferObject*>(Constructor::GetVideoMemory()->AllocateVertexBuffer(size_in_bytes));
//				m_vertex_buffer->Bind();
//				m_vertex_buffer->CopyData(vbuffer, m_vb_size);
//				m_vertex_buffer->Unbind();
//
//				m_was_modified = true;
//			}
//
//			void SetIndexBuffer(const std::vector<CurrentIndex>& ib)
//			{
//				SetIndexBuffer(&ib[0], sizeof(CurrentIndex)*ib.size());
//			}
//
//			void SetIndexBuffer(const IIndexArray* ib)
//			{
//				SetIndexBuffer(ib->GetIndexBuffer(), ib->GetMemoryUsage());
//			}
//
//			void SetIndexBuffer(const void* ibuffer, unsigned size)
//			{
//				m_index_count = size / sizeof(CurrentIndex);
//
//				m_index_buffer = dynamic_cast<IndexBufferObject*>(Constructor::GetVideoMemory()->AllocateIndexBuffer(size));
//				m_index_buffer->Bind();
//				m_index_buffer->CopyData(ibuffer, size);
//				m_index_buffer->Unbind();
//
//				m_was_modified = true;
//				m_ib_size = size;
//			}
//
//			bool Cook()
//			{
//				if (glGetError() != GL_NO_ERROR)
//					throw OpenGLException(L"Error came from upper subroutine to me... Will not work");
//
//				if (!m_vertex_buffer)
//					throw OpenGLException(L"Can't create VAO due to bad vertex buffer");
//
//				if (!m_index_buffer)
//					throw OpenGLException(L"Can't create VAO due to bad index buffer");
//
//				if (m_vao)
//				{
//					GL_CALL(glDeleteVertexArrays(1, &m_vao));
//				}
//
//				GL_CALL(glGenVertexArrays(1, &m_vao));
//				GL_CALL(glBindVertexArray(m_vao));
//
//				m_vertex_buffer->Bind();
//				m_index_buffer->Bind();
//				
//				AttributeConfiger<CurrentVertex> p(supported_by_context);
//
//				GL_CALL(glBindVertexArray(0));
//
//				return true;
//			}
//
//			void* MapVertexBuffer()
//			{
//				return m_vertex_buffer->Map();
//			}
//
//			const void* MapVertexBuffer() const
//			{
//				return m_vertex_buffer->Map();
//			}
//
//			void UnmapVertexBuffer()
//			{
//				m_vertex_buffer->Unmap();
//			}
//
//			void Clear()
//			{
//				Constructor::DestroyVertexBuffer(m_vertex_buffer);
//				m_vertex_buffer = nullptr;
//				Constructor::DestroyIndexBuffer(m_index_buffer);
//				m_index_buffer = nullptr;
//
//				if (m_vao)
//				{
//					GL_CALL(glDeleteVertexArrays(1, &m_vao));
//					m_vao = 0;
//				}
//			}
//
//			//			bool Save(std::ostream& stream) const
//			//			{
//			//				//if (!Renderable::Save(stream))
//			//				//	return (out_error() << "Can't save vertex array object " << std::endl, false);
//
//			//				//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));
//			//				//m_location.Save(stream);
//
//			//				const_cast<VertexArrayObject2<CurrentPrimitive, CurrentVertex>*>(this)->Bind(CurrentVertex::Value());
//
//			//				GLvoid* vb = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
//			//				stream.write(reinterpret_cast<const char*>(&m_vb_size), sizeof(m_vb_size));
//			//				stream.write(reinterpret_cast<const char*>(vb), m_vb_size);
//			//				stream.write(reinterpret_cast<const char*>(&m_vertex_size), sizeof(m_vertex_size));
//			//				glUnmapBuffer(GL_ARRAY_BUFFER);
//
//			//				GLvoid* ib = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
//			//				stream.write(reinterpret_cast<const char*>(&m_ib_size), sizeof(m_ib_size));
//			//				stream.write(reinterpret_cast<const char*>(ib), m_ib_size);
//			//				glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
//
//			//				stream.write(reinterpret_cast<const char*>(&m_index_count), sizeof(m_index_buffer));
//			//				int primitive_type = CurrentPrimitive;
//			//				stream.write(reinterpret_cast<const char*>(&primitive_type), sizeof(primitive_type));
//			//				stream.write(reinterpret_cast<const char*>(&m_was_modified), sizeof(m_was_modified));
//			//				int64_t combination = CurrentVertex::Value();
//			//				stream.write(reinterpret_cast<const char*>(&combination), sizeof(combination));
//			//				stream.write(reinterpret_cast<const char*>(&m_primitive_count), sizeof(m_primitive_count));
//
//			//				//			Clear();
//
//			//				return true;
//			//			}
//
//			//			bool Load(std::istream& stream)
//			//			{
//			//				//if (!Renderable::Load(stream))
//			//				//	return (out_error() << "Can't load vertex array object" << std::endl, false);
//
//			//				//stream.read(reinterpret_cast<char*>(&m_index), sizeof(m_index));
//			//				//m_location.Load(stream);
//			//				stream.read(reinterpret_cast<char*>(&m_vb_size), sizeof(m_vb_size));
//			//				char* vb = new char[m_vb_size];
//			//				try
//			//				{
//			//					stream.read(reinterpret_cast<char*>(vb), m_vb_size);
//			//					stream.read(reinterpret_cast<char*>(&m_vertex_size), sizeof(m_vertex_size));
//			//					SetVertexBuffer(vb, m_vb_size);
//			//				}
//			//				catch(...)
//			//				{
//			//					delete[] vb;
//			//                    throw System::PunkException(L"Failed to load vertex buffer");
//			//				}
//			//				delete[] vb;
//
//			//				stream.read(reinterpret_cast<char*>(&m_ib_size), sizeof(m_ib_size));
//			//				char* ib = new char[m_ib_size];
//			//				try
//			//				{
//			//					stream.read(reinterpret_cast<char*>(ib), m_ib_size);
//			//					SetIndexBuffer(ib, m_ib_size);
//			//				}
//			//				catch(...)
//			//				{
//			//					delete[] ib;
//			//                    throw System::PunkException(L"Failed to load vertex buffer");
//			//				}
//			//				delete[] ib;
//
//			//				stream.read(reinterpret_cast<char*>(&m_index_count), sizeof(m_index_buffer));
//			//				PrimitiveType primitive_type;
//			//				stream.read(reinterpret_cast<char*>(&primitive_type), sizeof(primitive_type));
//			//				stream.read(reinterpret_cast<char*>(&m_was_modified), sizeof(m_was_modified));
//			//				int combination;
//			//				stream.read(reinterpret_cast<char*>(&combination), sizeof(combination));
//			//				stream.read(reinterpret_cast<char*>(&m_primitive_count), sizeof(m_primitive_count));
//
//			//				if (primitive_type != CurrentPrimitive)
//			//				{
//			//					out_error() << "Bad primitive format " << AsString(primitive_type) << ". Expected " << AsString(CurrentPrimitive) << "." << std::endl;
//			//					return false;
//			//				}
//
//			//				if (combination != CurrentVertex::Value())
//			//				{
//			//					out_error() << "Bad vertex type format " << AsString(primitive_type) << ". Expected " << CurrentVertex::Value() << "." << std::endl;
//			//					return false;
//			//				}
//
//			//				Cook();
//
//			//				return true;
//			//			}
//
//			virtual bool HasData() const override
//			{
//				return m_index_buffer != nullptr && m_vertex_buffer != nullptr;
//			}
//
//			virtual size_t GetMemoryUsage() override
//			{
//				size_t res = 0;
//				if (m_index_buffer != 0)
//					res += m_index_buffer->GetSize();
//				if (m_vertex_buffer != 0)
//					res += m_vertex_buffer->GetSize();
//				return res;
//			}
//		};
//	};
//}
//PUNK_ENGINE_END
//
//#endif
