#include "gl_exceptions.h"
#include "../../../../../system/errors/module.h"
#include "gl_error_check.h"
#include "../extensions.h"

namespace Gpu
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
            case GL_INVALID_ENUM: throw OpenGLInvalidEnumException(msg);
            case GL_INVALID_VALUE: throw OpenGLInvalidValueException(msg);
            case GL_INVALID_OPERATION: throw OpenGLInvalidOperationException(msg);
            case GL_INVALID_FRAMEBUFFER_OPERATION: throw OpenGLInvalidFrameBufferOperationException(msg);
            case GL_OUT_OF_MEMORY: throw OpenGLOutOfMemoryException(msg);
            default: throw OpenGLException(msg);
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
			case GL_INVALID_ENUM: throw OpenGLInvalidEnumException(msg);
			case GL_INVALID_VALUE: throw OpenGLInvalidValueException(msg);
			case GL_INVALID_OPERATION: throw OpenGLInvalidOperationException(msg);
			case GL_INVALID_FRAMEBUFFER_OPERATION: throw OpenGLInvalidFrameBufferOperationException(msg);
			case GL_OUT_OF_MEMORY: throw OpenGLOutOfMemoryException(msg);
			default: throw OpenGLException(msg);
			};
#else
            (void)msg;
#endif  //	_DEBUG
		}
	}
}
