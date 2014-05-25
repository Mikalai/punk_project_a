#ifndef _H_GL_BATCH
#define _H_GL_BATCH

#include <config.h>
#include <graphics/primitives/irenderable.h>
#include "gl_vertex_array_object.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		template<typename IT, typename ... VC>
		struct GlBatchCore {
			using VertexArrayObjectType = VertexArrayObject2 < VertexBufferObject<Vertex<VC...>>, IndexBufferObject<IT> >;

			GlBatchCore() {
				m_vao = new VertexArrayObjectType;
			}			

			~GlBatchCore() {
				delete m_vao;
				m_vao = nullptr;
			}

			VertexArrayObjectType* m_vao{ nullptr };
		};

		template<PrimitiveType CurrentPrimitiveType, typename IT, typename ... VC> struct RenderPolicy {};			

		template<PrimitiveType CurrentPrimitiveType, typename ... VC>
		struct RenderPolicy<CurrentPrimitiveType, std::uint16_t, VC...> {
			using IndexType = std::uint16_t;
			static void Render(GlBatchCore<IndexType, VC...>& core) {
				GLenum type = PrimitiveTypeToOpenGL(CurrentPrimitiveType);				
				GL_CALL(glDrawElements(type, core.m_vao->GetIndexCount(), GL_SHORT, 0));
			}
		};

		template<PrimitiveType CurrentPrimitiveType, typename ... VC>
		struct RenderPolicy<CurrentPrimitiveType, std::uint32_t, VC...> {
			using IndexType = std::uint32_t;
			static void Render(GlBatchCore<IndexType, VC...>& core) {
				GLenum type = PrimitiveTypeToOpenGL(CurrentPrimitiveType);				
				GL_CALL(glDrawElements(type, core.m_vao->GetIndexCount(), GL_UNSIGNED_INT, 0));				
			}
		};

		template<PrimitiveType CurrentPrimitiveType, typename ... VC>
		struct RenderPolicy<CurrentPrimitiveType, std::nullptr_t, VC...> {
			using IndexType = std::nullptr_t;
			static void Render(GlBatchCore<IndexType, VC...>& core) {
				GLenum type = PrimitiveTypeToOpenGL(CurrentPrimitiveType);				
				GL_CALL(glDrawArrays(type, 0, core.m_vao->GetVertexCount()));				
			}
		};

		template<PrimitiveType CurrentPrimitiveType, typename IT, typename ... VC>
		class GlBatch : public IRenderable {
		public:
			using CurrentVertexArrayObject = VertexArrayObject2 < VertexBufferObject<Vertex<VC...>>, IndexBufferObject<IT> > ;
			using CurrentRenderPolicy = RenderPolicy < CurrentPrimitiveType, IT, VC... > ;
			using CurrentBatchCore = GlBatchCore < IT, VC... > ;
		public:

			GlBatch() {}

			virtual ~GlBatch() {}

			void QueryInterface(const Core::Guid& type, void** object) override {
				Core::QueryInterface(this, type, object, { Core::IID_IObject });
			}

			void Bind() override {
				m_core.m_vao->Bind();
			}

			void Unbind() override {
				m_core.m_vao->Unbind();
			}

			void Render() override {
				CurrentRenderPolicy::Render(m_core);
			}

			std::uint64_t GetMemoryUsage() override {
				return 0;
			}

			bool HasData() const override {
				return true;
			}

			void Cook(VertexArray<Vertex<VC...>>* vb, IndexArray<IT>* ib) {
				m_core.m_vao->Cook(vb, ib);
			}

		private:

			void Cook(IVertexArray* vb, IIndexArray* ib) {
				Cook((VertexArray<Vertex<VC...>>*)vb, (IndexArray<IT>*)ib);
			}			

			CurrentBatchCore m_core;
			PUNK_OBJECT_DEFAULT_IMPL(GlBatch);
		};
	};
}
PUNK_ENGINE_END

#endif	//	_H_GL_BATCH