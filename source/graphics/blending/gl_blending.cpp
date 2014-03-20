#include <graphics/error/module.h>
#include "gl_blending.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
		GLenum BlendFunctionToOpenGL(BlendFunction value)
		{
			switch (value)
			{
			case BlendFunction::One:
				return GL_ONE;
			case BlendFunction::SourceAlpha:
				return GL_SRC_ALPHA;
			case BlendFunction::OneMinusSrcAlpha:
				return GL_ONE_MINUS_SRC_ALPHA;
			default:
                throw Error::GraphicsException(L"Invalid blend function");
			}
		}
	}
}
PUNK_ENGINE_END
