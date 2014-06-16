#ifndef _H_PUNK_OPENGL_EXCEPTIONS
#define _H_PUNK_OPENGL_EXCEPTIONS

#include <graphics/error/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
		namespace Error {
			class PUNK_ENGINE_API OpenGLException : public Graphics::Error::GraphicsException {
				using GraphicsException::GraphicsException;
			};

			class PUNK_ENGINE_API OpenGLNotImplemented : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidEnumException : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidValueException : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidOperationException : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidFrameBufferOperationException : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLOutOfMemoryException : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API CreateOpenGLContextError : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLContextMakeCurrentError : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLCreateContextError : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidImageDataType : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidTextureFilter : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidTextureWrapMode : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidTextureCompareFunc : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidTextureCompareMode : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidTextureWrapDirection : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidImageFormat : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLUnsupportedCoverageSamplesCount : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLUnsupportedDepthSamplesCount : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API OpenGLInvalidFramebuffer : public OpenGLException {
				using OpenGLException::OpenGLException;
			};

			class PUNK_ENGINE_API InvalidFrameBufferTarget : public OpenGLException {
				using OpenGLException::OpenGLException;
			};
		}
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_EXCEPTIONS
