#ifndef _H_PUNK_OPENGL_EXCEPTIONS
#define _H_PUNK_OPENGL_EXCEPTIONS

#include <graphics/error/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class PUNK_ENGINE_API OpenGLException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLNotImplemented : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidEnumException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidValueException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidOperationException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidFrameBufferOperationException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLOutOfMemoryException : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API CreateOpenGLContextError : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLContextMakeCurrentError : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLCreateContextError : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidImageDataType : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidTextureFilter : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidTextureWrapMode : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidTextureCompareFunc : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidTextureCompareMode : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidTextureWrapDirection : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidImageFormat : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLUnsupportedCoverageSamplesCount : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLUnsupportedDepthSamplesCount : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };

        class PUNK_ENGINE_API OpenGLInvalidFramebuffer : public Error::GraphicsException {
            using GraphicsException::GraphicsException;
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_EXCEPTIONS
