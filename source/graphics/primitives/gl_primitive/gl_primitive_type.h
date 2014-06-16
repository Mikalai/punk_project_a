#ifndef _H_PUNK_GPU_OPENGL_PRIMITVE_TYPE
#define _H_PUNK_GPU_OPENGL_PRIMITVE_TYPE

#include <graphics/primitives/primitive_type.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {
        extern PUNK_ENGINE_LOCAL GLenum PrimitiveTypeToOpenGL(PrimitiveType type);
		extern PUNK_ENGINE_LOCAL PrimitiveType HighLevelPrimitiveTypeToBasic(PrimitiveType type);
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_OPENGL_PRIMITVE_TYPE
