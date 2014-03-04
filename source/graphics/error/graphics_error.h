#ifndef _H_PUNK_GPU_EXCPETION
#define _H_PUNK_GPU_EXCPETION

#include <system/errors/exceptions.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace Error{

        class PUNK_ENGINE_API GraphicsException : public System::Error::SystemException {
            using SystemException::SystemException;
        };

        class PUNK_ENGINE_API ChoosePixelFormatError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API SetPixelFormatError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API CreateOpenGLContextError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLContextMakeCurrentError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLCreateContextError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_EXCPETION
