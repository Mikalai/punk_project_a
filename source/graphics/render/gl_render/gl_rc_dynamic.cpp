//#include "gl_rc_dynamic.h"
//#include <graphics/render/render_context/gl_ishader.h>
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//    namespace OpenGL {
//
//        DynamicRenderContext::DynamicRenderContext(RenderContextType policy)
//            : GlRenderContextBase(policy)
//		{}
//
//		void DynamicRenderContext::SetShaders(IShader *vs, IShader *fs, IShader *gs)
//		{
//            if ((m_vertex_shader = vs))
//				m_vertex_shader->Connect(this);
//            if ((m_fragment_shader = fs))
//				m_fragment_shader->Connect(this);
//            if ((m_geometry_shader = gs))
//				m_geometry_shader->Connect(this);
//			Init();
//		}
//
//		
//
//		void DynamicRenderContext::BindParameters(const CoreState& params)
//		{
//			
//		}
//
//		int64_t DynamicRenderContext::GetRequiredAttributesSet() const
//		{
//            int64_t result = 0;
//			result |= m_vertex_shader->GetRequiredAttributesSet();
//			result |= m_fragment_shader->GetRequiredAttributesSet();
//			if (m_geometry_shader)
//				result |= m_geometry_shader->GetRequiredAttributesSet();
//			return result;
//		}
//	}
//}
//PUNK_ENGINE_END
