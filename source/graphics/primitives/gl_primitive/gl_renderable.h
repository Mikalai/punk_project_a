//#ifndef _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT
//#define _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT
//
//#include <vector>
//#include <graphics/buffers/vbo.h>
//#include <graphics/buffers/ibo.h>
//#include <graphics/video_driver/module.h>
//#include <graphics/primitives/vertex_array.h>
//#include <graphics/primitives/index_array.h>
//#include <graphics/video_driver/module.h>
//#include <graphics/video_memory/module.h>
//#include <graphics/primitives/irenderable.h>
//#include "gl_attribute_configer.h"
//#include "gl_primitive_type.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//	namespace OpenGL
//	{
//		
//		class PUNK_ENGINE_LOCAL GlRenderable : public IRenderable
//		{
//		public:
//			GlRenderable(IVideoDriver* driver);
//			virtual ~GlRenderable();
//			void Bind(std::int64_t) override;
//			void Unbind() override;
//			void Render() override;
//			std::uint64_t GetMemoryUsage() override;
//			bool HasData() const override;
//			void Cook(PrimitiveType type, IVertexArray* vb, IIndexArray* ib) override;
//		private:
//			IVideoDriver* m_driver{ nullptr };
//			GLuint m_index_count;
//			GLuint m_vao;
//			unsigned m_vertex_size;
//			bool m_was_modified;
//			unsigned m_primitive_count;
//			int m_vb_size;
//			int m_ib_size;
//			IndexBufferObject* m_index_buffer;
//			VertexBufferObject* m_vertex_buffer;
//
//		public:			
//		}
//	};
//
//	template<class Vertex>
//	GlRenderable* CreateRenderable() {
//
//	}
//}
//PUNK_ENGINE_END
//
//#endif
