#include <graphics/opengl/module.h>
#include "gl_exceptions.h"
#include "gl_error_check.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        void ValidateOpenGL(const wchar_t* msg)
        {
#ifdef _DEBUG
            GLenum error = glGetError();
            switch(error)
            {
            case GL_NO_ERROR: break;
			case GL_INVALID_ENUM: throw Error::OpenGLInvalidEnumException(msg);
			case GL_INVALID_VALUE: throw Error::OpenGLInvalidValueException(msg);
			case GL_INVALID_OPERATION: throw Error::OpenGLInvalidOperationException(msg);
			case GL_INVALID_FRAMEBUFFER_OPERATION: throw Error::OpenGLInvalidFrameBufferOperationException(msg);
			case GL_OUT_OF_MEMORY: throw Error::OpenGLOutOfMemoryException(msg);
			default: throw Error::OpenGLException(msg);
            };
#else
            (void)msg;
#endif  //	_DEBUG

        }

        void ValidateOpenGL(const char* msg)
		{
#ifdef _DEBUG
			GLenum error = glGetError();
			switch(error)
			{
			case GL_NO_ERROR: break;
			case GL_INVALID_ENUM: throw Error::OpenGLInvalidEnumException(msg);
			case GL_INVALID_VALUE: throw Error::OpenGLInvalidValueException(msg);
			case GL_INVALID_OPERATION: throw Error::OpenGLInvalidOperationException(msg);
			case GL_INVALID_FRAMEBUFFER_OPERATION: throw Error::OpenGLInvalidFrameBufferOperationException(msg);
			case GL_OUT_OF_MEMORY: throw Error::OpenGLOutOfMemoryException(msg);
			default: throw Error::OpenGLException(msg);
			};
#else
            (void)msg;
#endif  //	_DEBUG
		}
	}
}
PUNK_ENGINE_END
