#ifndef _H_PUNK_OPENGL_PARTICLE
#define _H_PUNK_OPENGL_SHADER_GRASS

#include "gl_render_context_base.h"
#include "gl_shader_type.h"
#include "gl_shader.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		template<RenderContextType ContextType> 
		class GlRenderContext : public GlRenderContextBase {
		public:
			GlRenderContext() 
			: GlRenderContextBase(ContextType) {
				SetShaders(
					new Shader<ShaderType::Vertex, ContextType>,
					new Shader<ShaderType::Fragment, ContextType>,
					new Shader<ShaderType::Geometry, ContextType, NoShaderAspect>);
			}
		};
	}
}
PUNK_ENGINE_END

#endif
