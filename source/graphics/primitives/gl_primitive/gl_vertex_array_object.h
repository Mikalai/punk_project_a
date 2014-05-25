#ifndef _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT
#define _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT

#include <vector>
#include <graphics/buffers/vbo.h>
#include <graphics/buffers/ibo.h>
#include <graphics/video_driver/module.h>
#include <graphics/primitives/renderable.h>
#include <graphics/primitives/vertex_array.h>
#include <graphics/primitives/index_array.h>
#include <graphics/video_driver/module.h>
#include <graphics/video_memory/module.h>
#include "gl_attribute_configer.h"
#include "gl_primitive_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		template<template<typename V, typename T, typename...> class T, typename>
		struct instantiate_with_arg_pack { };

		template<
			typename TT, typename VV,
			template<typename V, typename T, typename...> class T,
			template<typename V, typename T, typename...> class U,
			typename... Ts
		>
		struct instantiate_with_arg_pack < T, U<TT, VV, Ts...> >
		{
			using type = T < TT, VV, Ts... > ;
		};

		template<class VB, class IB>
		struct VaoCore {
			using CurrentVertex = typename VB::CurrentVertex;
			using CurrentIndex = typename IB::CurrentIndex;

			IVideoDriver* m_driver{ nullptr };
			GLuint m_index_count{ 0 };
			GLuint m_vao{ 0 };
			unsigned m_vertex_size{ 0 };
			bool m_was_modified{ true };
			unsigned m_primitive_count{ 0 };
			int m_vb_size{ 0 };
			int m_ib_size{ 0 };
			IndexBufferObject<CurrentIndex>* m_index_buffer{ nullptr };
			VertexBufferObject<CurrentVertex>* m_vertex_buffer{ nullptr };
		};

		template<class VB>
		struct VaoCore < VB, IndexBufferObject<std::nullptr_t> > {
			using CurrentVertex = typename VB::CurrentVertex;
			using CurrentIndex = std::nullptr_t;
			IVideoDriver* m_driver{ nullptr };
			GLuint m_vao{ 0 };
			unsigned m_vertex_size{ 0 };
			bool m_was_modified{ true };
			unsigned m_primitive_count{ 0 };
			int m_vb_size{ 0 };
			VertexBufferObject<CurrentVertex>* m_vertex_buffer{ nullptr };
		};

		template<class VB, class IB> struct VaoAccessorPolicy {
			VaoAccessorPolicy(VaoCore<VB, IB>& core)
				: m_core{ core } {}

			std::uint32_t GetIndexCount() {
				if (m_core.m_index_buffer)
					return m_core.m_index_buffer->GetCount();
				return -1;
			}

			std::uint32_t GetVertexCount() {
				if (m_core.m_vertex_buffer)
					return m_core.m_vertex_buffer->GetVertexCount();
				return -1;
			}

			std::uint32_t GetMemoryUsage() {
				std::uint32_t res = 0;
				if (m_core.m_index_buffer != 0)
					res += m_core.m_index_buffer->GetSize();
				if (m_core.m_vertex_buffer != 0)
					res += m_core.m_vertex_buffer->GetSize();
				return res;
			}

			bool HasData() const {
				return m_index_buffer != nullptr && m_vertex_buffer != nullptr;
			}

			void Clear() {
				delete m_core.m_vertex_buffer;
				m_core.m_vertex_buffer = nullptr;
				delete m_core.m_index_buffer;
				m_core.m_index_buffer = nullptr;

				if (m_core.m_vao) {
					GL_CALL(glDeleteVertexArrays(1, &m_core.m_vao));
					m_core.m_vao = 0;
				}
			}

			typename VB::CurrentVertex* MapVertexBuffer()
			{
				return m_core.m_vertex_buffer->MapVB();
			}

			const typename VB::CurrentVertex* MapVertexBuffer() const
			{
				return m_core.m_vertex_buffer->MapVB();
			}

			void UnmapVertexBuffer()
			{
				m_core.m_vertex_buffer->Unmap();
			}

			typename IB::CurrentIndex* MapIndexBuffer() {
				return m_core.m_index_buffer->MapIB();
			}

			const typename IB::CurrentIndex* MapIndexBuffer() const {
				return m_core.m_index_buffer->MapIB();
			}

			void UnmapIndexBuffer() {
				m_core.m_index_buffer->Unmap();
			}

			VaoCore<VB, IB>& m_core;
		};

		template<class VB> struct VaoAccessorPolicy < VB, IndexBufferObject<std::nullptr_t> > {
			VaoAccessorPolicy(VaoCore<VB, IndexBufferObject<std::nullptr_t>>& core)
				: m_core{ core } {}

			std::uint32_t GetVertexCount() {
				if (m_core.m_vertex_buffer)
					return m_core.m_vertex_buffer->GetVertexCount();
				return -1;
			}

			std::uint32_t GetMemoryUsage()
			{
				std::uint32_t res = 0;
				if (m_core.m_vertex_buffer != 0)
					res += m_core.m_vertex_buffer->GetSize();
				return res;
			}

			bool HasData() const {
				return m_core.m_vertex_buffer != nullptr;
			}

			void Clear() {
				delete m_core.m_vertex_buffer;
				m_core.m_vertex_buffer = nullptr;

				if (m_core.m_vao) {
					GL_CALL(glDeleteVertexArrays(1, &m_core.m_vao));
					m_core.m_vao = 0;
				}
			}

			typename VB::CurrentVertex* MapVertexBuffer()
			{
				return m_core.m_vertex_buffer->Map();
			}

			const typename VB::CurrentVertex* MapVertexBuffer() const
			{
				return m_core.m_vertex_buffer->Map();
			}

			void UnmapVertexBuffer()
			{
				m_core.m_vertex_buffer->Unmap();
			}

			VaoCore<VB, IndexBufferObject<std::nullptr_t>>& m_core;
		};

		template<typename Vertex, typename Index>
		struct VaoCookPolicy {
			
			using CurrentConfigurer = instantiate_with_arg_pack < AttributeConfigure, Vertex >;

			VaoCookPolicy(VaoCore<VertexBufferObject<Vertex>, IndexBufferObject<Index>>& core)
				: m_core{ core }
			{}

			bool Cook(VertexArray<Vertex>* vb, IndexArray<Index>* ib)
			{
				if (glGetError() != GL_NO_ERROR)
					throw OpenGLException(L"Error came from upper subroutine to me... Will not work");

				if (m_core.m_vertex_buffer) {
					delete m_core.m_vertex_buffer;
				}
				m_core.m_vertex_buffer = new VertexBufferObject < Vertex >;
				m_core.m_vertex_buffer->Bind();
				m_core.m_vertex_buffer->CopyData(vb->GetVertexBuffer(), vb->GetVertexCount());
				m_core.m_vertex_buffer->Unbind();

				if (m_core.m_index_buffer)
					delete m_core.m_index_buffer;
				m_core.m_index_buffer = new IndexBufferObject < Index >;
				m_core.m_index_buffer->Bind();
				m_core.m_index_buffer->CopyData(ib->GetIndexBuffer(), ib->GetIndexCount());
				m_core.m_index_buffer->Unbind();

				if (m_core.m_vao)
				{
					GL_CALL(glDeleteVertexArrays(1, &m_core.m_vao));
				}

				GL_CALL(glGenVertexArrays(1, &m_core.m_vao));
				GL_CALL(glBindVertexArray(m_core.m_vao));

				m_core.m_vertex_buffer->Bind();
				m_core.m_index_buffer->Bind();

				CurrentConfigurer p{};

				GL_CALL(glBindVertexArray(0));

				return true;
			}

			VaoCore<VertexBufferObject<Vertex>, IndexBufferObject<Index>>& m_core;
		};

		template<typename Vertex>
		struct VaoCookPolicy<Vertex, std::nullptr_t> {

			using CurrentConfigurer = instantiate_with_arg_pack < AttributeConfigure, Vertex >;

			VaoCookPolicy(VaoCore<VertexBufferObject<Vertex>, IndexBufferObject<std::nullptr_t>>& core)
				: m_core{ core }
			{}

			bool Cook(VertexArray<Vertex>* vb, IndexArray<std::nullptr_t>* ib)
			{
				if (glGetError() != GL_NO_ERROR)
					throw OpenGLException(L"Error came from upper subroutine to me... Will not work");

				if (m_core.m_vertex_buffer) {
					delete m_core.m_vertex_buffer;
				}
				m_core.m_vertex_buffer = new VertexBufferObject < Vertex >;
				m_core.m_vertex_buffer->Bind();
				m_core.m_vertex_buffer->CopyData(vb->GetVertexBuffer(), vb->GetVertexCount());
				m_core.m_vertex_buffer->Unbind();
				
				if (m_core.m_vao)
				{
					GL_CALL(glDeleteVertexArrays(1, &m_core.m_vao));
				}

				GL_CALL(glGenVertexArrays(1, &m_core.m_vao));
				GL_CALL(glBindVertexArray(m_core.m_vao));

				m_core.m_vertex_buffer->Bind();

				CurrentConfigurer p{};

				GL_CALL(glBindVertexArray(0));

				return true;
			}

			VaoCore<VertexBufferObject<Vertex>, IndexBufferObject<std::nullptr_t>>& m_core;
		};



		template<class VB, class IB>
		class PUNK_ENGINE_LOCAL VertexArrayObject2 
			: public VaoAccessorPolicy<VB, IB>
			, public VaoCookPolicy<typename VB::CurrentVertex, typename IB::CurrentIndex>
		{
		public:
			using CurrentVertex = typename VB::CurrentVertex;
			using CurrentIndex = typename IB::CurrentIndex;
		protected:			
			using CurrentVaoCore = VaoCore < VB, IB > ;
			CurrentVaoCore m_core;
		public:
			VertexArrayObject2() 
				: VaoAccessorPolicy<VB, IB>(m_core)
				, VaoCookPolicy<CurrentVertex, CurrentIndex>(m_core)
			{}

			~VertexArrayObject2()
			{
				Clear();
			}
		
			void Bind()
			{
				GL_CALL(glBindVertexArray(m_core.m_vao));
			}

			void Unbind()
			{
				GL_CALL(glBindVertexArray(0));
				for (int i = 0; i < 16; i++)
				{
					GL_CALL(glDisableVertexAttribArray(i));
				}
			}										
		};	
	}
}
PUNK_ENGINE_END

#endif
