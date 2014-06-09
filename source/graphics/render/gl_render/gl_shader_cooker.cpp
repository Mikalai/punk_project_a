#include <config.h>
#include "gl_shader_cooker.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics {
	namespace OpenGL {

		System::ILogger* ShaderCooker::m_logger = System::GetDefaultLogger();

		GLuint ShaderCooker::CookFromFile(ShaderType type, const Core::String& filename) {
			Core::Buffer shader_data;
			System::BinaryFile::Load(filename, shader_data);			
			m_logger->Info(L"Loading vertex shader " + filename);
			const char* body = (const char*)shader_data.Data();
			int len = shader_data.GetSize();
			return CookFromString(type, body, len);			
		}

		GLuint ShaderCooker::CookFromFileWithHeaders(ShaderType type, const Core::String& filename, int count, const char** names) {
			Core::Buffer shader_data;
			System::BinaryFile::Load(filename, shader_data);
			m_logger->Info(L"Loading vertex shader " + filename);
			const char* body = (const char*)shader_data.Data();
			int len = shader_data.GetSize();
			return CookFromStringWithHeaders(type, body, len, count, names);
		}

		GLuint ShaderCooker::CookFromString(ShaderType type, const char* string, unsigned length) {
			GL_CALL(GLuint shader_index = glCreateShader(ConvertShaderTypeToOpenGL(type)));
			const char * body = string;
			int len = length;
			GLint compileStatus;
			GL_CALL(glShaderSource(shader_index, 1, (const char**)&body, &len));
			GL_CALL(glCompileShader(shader_index));
			GL_CALL(glGetShaderiv(shader_index, GL_COMPILE_STATUS, &compileStatus));
			if (compileStatus == GL_TRUE) {
				m_logger->Info(L"Shader has been compiled successfully");
			}
			else
			{
				GLint logLength;
				GL_CALL(glGetShaderiv(shader_index, GL_INFO_LOG_LENGTH, &logLength));
				std::vector<char> buffer(logLength);
				GL_CALL(glGetShaderInfoLog(shader_index, logLength, NULL, &buffer[0]));
				Core::String message = Core::String(L"Can't create vertex shader: {0}\n").arg(Core::String(&buffer[0], buffer.size()));
				throw Error::OpenGLException(message);
			}
			return shader_index;
		}

		GLuint ShaderCooker::CookFromStringWithHeaders(ShaderType type, const char* data, unsigned length, int count, const char** names) {
			GL_CALL(GLuint shader_index = glCreateShader(ConvertShaderTypeToOpenGL(type)));
			const char * body = data;
			int len = length;
			GLint compileStatus;
			GL_CALL(glShaderSource(shader_index, 1, (const char**)&body, &len));
			GL_CALL(glCompileShaderIncludeARB(shader_index, count, names, nullptr));
			GL_CALL(glGetShaderiv(shader_index, GL_COMPILE_STATUS, &compileStatus));
			if (compileStatus == GL_TRUE)
			{
				m_logger->Info(L"Shader has been compiled successfully");
			}
			else
			{
				GLint logLength;
				GL_CALL(glGetShaderiv(shader_index, GL_INFO_LOG_LENGTH, &logLength));
				std::vector<char> buffer(logLength);
				GL_CALL(glGetShaderInfoLog(shader_index, logLength, NULL, &buffer[0]));
				Core::String message = Core::String(L"Can't create vertex shader: {0}\n").arg(Core::String(&buffer[0], buffer.size()));
				throw Error::OpenGLException(message);
			}
			return shader_index;
		}
	}
}
PUNK_ENGINE_END
