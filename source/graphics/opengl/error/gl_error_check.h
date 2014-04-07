#ifndef _H_PUNK_OPENGL_ERROR_CHECK
#define _H_PUNK_OPENGL_ERROR_CHECK

#include <config.h>
#ifdef _DEBUG
#define GL_CALL(X) X; ValidateOpenGL(#X)
#else
#define GL_CALL(X) X;
#endif

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        extern void ValidateOpenGL(const char* msg);
        extern void ValidateOpenGL(const wchar_t* msg);
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_ERROR_CHECK
