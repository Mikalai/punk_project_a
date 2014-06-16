#ifndef _H_PUNK_OPENGL_DRIVER_SHADER_BASE
#define _H_PUNK_OPENGL_DRIVER_SHADER_BASE

#include <memory>
#include <config.h>
#include <graphics/render/ishader.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
}

namespace Graphics {

	class CoreState;

	namespace OpenGL
	{
		class GlRenderContextBase;

		class PUNK_ENGINE_LOCAL ShaderBase : public IShader
		{			
		public:
			virtual ~ShaderBase();
			virtual void Connect(GlRenderContextBase* rc) = 0;
			virtual void Initialize() = 0;
			virtual void ApplyState(const CoreState& state) = 0;
			virtual GLuint GetIndex() const = 0;

        protected:
			bool m_initiailized{ false };
			GlRenderContextBase* m_rc{ nullptr };			
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_DRIVER_SHADER_BASE
