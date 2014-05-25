#include "gl_primitive_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

		extern PUNK_ENGINE_LOCAL PrimitiveType HighLevelPrimitiveTypeToBasic(PrimitiveType type) {
			switch (type)
			{
			case PrimitiveType::POINTS:
				return PrimitiveType::POINTS;
			case PrimitiveType::LINE_STRIP:
				return PrimitiveType::LINE_STRIP;
			case PrimitiveType::LINE_LOOP:
				return PrimitiveType::LINE_LOOP;
			case PrimitiveType::LINES:
				return PrimitiveType::LINES;
			case PrimitiveType::LINE_STRIP_ADJANCECY:
				return PrimitiveType::LINE_STRIP_ADJANCECY;
			case PrimitiveType::LINES_ADJANCENCY:
				return PrimitiveType::LINES_ADJANCENCY;
			case PrimitiveType::TRIANGLE_STRIP:
				return PrimitiveType::TRIANGLE_STRIP;
			case PrimitiveType::TRIANGLE_FAN:
				return PrimitiveType::TRIANGLE_FAN;
			case PrimitiveType::TRIANGLES:
				return PrimitiveType::TRIANGLES;
			case PrimitiveType::TRIANGLE_STRIP_ADJANCECY:
				return PrimitiveType::TRIANGLE_STRIP_ADJANCECY;
			case PrimitiveType::TRIANGLES_ADJANCECY:
				return PrimitiveType::TRIANGLES_ADJANCECY;
			case PrimitiveType::QUADS:	//	if QUADS are used, they should be internally converted to triangles
				return PrimitiveType::TRIANGLES;
			default:
				throw OpenGLException(L"Unsupported primitive type");
			}
		}

		extern PUNK_ENGINE_LOCAL GLenum PrimitiveTypeToOpenGL(PrimitiveType type)
		{
			switch (type)
			{
            case PrimitiveType::POINTS:
				return GL_POINTS;
            case PrimitiveType::LINE_STRIP:
				return GL_LINE_STRIP;
            case PrimitiveType::LINE_LOOP:
				return GL_LINE_LOOP;
            case PrimitiveType::LINES:
				return GL_LINES;
            case PrimitiveType::LINE_STRIP_ADJANCECY:
				return GL_LINE_STRIP_ADJACENCY;
            case PrimitiveType::LINES_ADJANCENCY:
				return GL_LINES_ADJACENCY;
            case PrimitiveType::TRIANGLE_STRIP:
				return GL_TRIANGLE_STRIP;
            case PrimitiveType::TRIANGLE_FAN:
                return GL_TRIANGLE_FAN;
            case PrimitiveType::TRIANGLES:
				return GL_TRIANGLES;
            case PrimitiveType::TRIANGLE_STRIP_ADJANCECY:
				return GL_TRIANGLE_STRIP_ADJACENCY;
            case PrimitiveType::TRIANGLES_ADJANCECY:
				return GL_TRIANGLES_ADJACENCY;
            case PrimitiveType::QUADS:	//	if QUADS are used, they should be internally converted to triangles
				return GL_TRIANGLES;
            default:
                throw OpenGLException(L"Unsupported primitive type");
			}
		}
	}
}
PUNK_ENGINE_END
