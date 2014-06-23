#ifndef GL_BLENDING_H
#define GL_BLENDING_H

#include <graphics/blending/module.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {
		GLenum BlendFunctionToOpenGL(BlendFunction value);
	}
}
PUNK_ENGINE_END

#endif // GL_BLENDING_H
