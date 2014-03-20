#ifndef _H_PUNK_OPENGL_DRIVER_SHADER
#define _H_PUNK_OPENGL_DRIVER_SHADER

#include <memory>
#include <config.h>
#include <system/environment.h>
#include <system/filesystem/module.h>
#include <graphics/state/module.h>
#include <graphics/opengl/module.h>
#include <graphics/error/module.h>
#include <graphics/primitives/module.h>
#include <graphics/shaders/gl_shaders/gl_shader_types/module.h>
#include <graphics/render/render_context/gl_render_context/gl_rc_dynamic.h>
#include "gl_shader_type.h"

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
}

namespace Graphics {

	class CoreState;

	namespace OpenGL
	{
		class DynamicRenderContext;

		class Shader
		{			
		public:
			explicit Shader(ShaderType type);			
			~Shader();

			void CookFromFile(const Core::String& filename);
            void CookFromFileWithHeaders(const Core::String& filename, int count, const char** names);
			void CookFromString(const char* filename, unsigned length);
            void CookFromStringWithHeaders(const char* data, unsigned length, int count, const char** names);

			unsigned GetIndex() const;

			void Connect(DynamicRenderContext* rc);
			virtual void InitUniforms() {}
            virtual void BindParameters(const CoreState&) {}
			virtual int64_t GetRequiredAttributesSet() const { return 0; }            

        protected:
			DynamicRenderContext* m_rc;
			GLuint m_shader_index;
			GLenum m_type;

			Shader(const Shader& shader) = delete;
			Shader& operator = (const Shader& shader) = delete;
		};

		struct NoShader {};
	}
}
PUNK_ENGINE_END

#endif
