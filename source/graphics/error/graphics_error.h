#ifndef _H_PUNK_Graphics_EXCPETION
#define _H_PUNK_Graphics_EXCPETION

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

        class PUNK_ENGINE_API CantSetFullscreenError : public GraphicsException {
            using GraphicsException::GraphicsException;
        };        

        class PUNK_ENGINE_API InvalidFrameBufferTarget : public GraphicsException {
            using GraphicsException::GraphicsException;
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_Graphics_EXCPETION
