//#include <graphics/render/irender_context.h>
//#include <graphics/render/gl_render/module.h>
//#include "gl_no_light_solid_color.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics
//{
//    static IRenderContext* g_rc[(int)RenderContextType::End];
//
//    IRenderContext* GetRenderContext(RenderContextType value) {
//        return g_rc[GetIndex(value)];
//    }
//
//    bool InitRenderContexts(IVideoDriver *driver) {
//        return OpenGL::InitRenderContexts(driver);
//    }
//
//    void DestroyRenderContexts() {
//        OpenGL::DestroyRenderContexts();
//    }
//
//    namespace OpenGL
//    {            
//        void DestroyRenderContexts() {
//            for (int i = 0; i < (int)RenderContextType::End; ++i) {
//                delete g_rc[i];
//                g_rc[i] = nullptr;
//            }
//        }
//
//		template<RenderContextType Policy>
//        void CreateRc() {
//            DynamicRenderContext* rc = new DynamicRenderContext(Policy);
//            
//			rc->SetShaders(new Shader<ShaderType::Vertex, Policy>
//				, new Shader<ShaderType::Fragment, Policy>
//				, new Shader<ShaderType::Geometry, Policy, NoShaderAspect>);
//
//            g_rc[GetIndex(Policy)] = rc;
//        }
//
//        bool InitRenderContexts(IVideoDriver* driver) {
//
//
//            return true;
//        }        
//    }
//}
//PUNK_ENGINE_END
