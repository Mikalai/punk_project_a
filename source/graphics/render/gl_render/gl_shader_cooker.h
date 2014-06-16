#ifndef _H_GL_SHADER_COOKER
#define _H_GL_SHADER_COOKER

#include <config.h>
#include <graphics/opengl/module.h>
#include <system/logger/module.h>
#include <graphics/render/gl_render/gl_shader_base.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics {
	namespace OpenGL {

		class PUNK_ENGINE_LOCAL ShaderCooker {
		public:
			static GLuint CookFromFile(ShaderType type, const Core::String& filename);
			static GLuint CookFromFileWithHeaders(ShaderType type, const Core::String& filename, int count, const char** names);
			static GLuint CookFromString(ShaderType type, const char* filename, unsigned length);
			static GLuint CookFromStringWithHeaders(ShaderType type, const char* data, unsigned length, int count, const char** names);
		private:
			static System::ILogger* m_logger;
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_GL_SHADER_COOKER