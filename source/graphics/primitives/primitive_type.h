#ifndef _H_PUNK_GPU_PRIMITIVE_TYPE
#define _H_PUNK_GPU_PRIMITIVE_TYPE

#include <config.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	enum class PrimitiveType { 
		POINTS, 
		LINE_STRIP, 
		LINE_LOOP, 
		LINES, 
		LINE_STRIP_ADJANCECY, 
		LINES_ADJANCENCY, 
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		TRIANGLE_STRIP_ADJANCECY,
		TRIANGLES_ADJANCECY,
		QUADS,
		POLYGON
	};

    extern PUNK_ENGINE_API const Core::String AsString(const PrimitiveType& value);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_PRIMITIVE_TYPE
