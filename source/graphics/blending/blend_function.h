#ifndef BLEND_FUNCTION_H
#define BLEND_FUNCTION_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics
{
	enum class BlendFunction {
		SourceAlpha,
		One,
		OneMinusSrcAlpha
	};

    extern PUNK_ENGINE_API const Core::String AsString(BlendFunction value);
}
PUNK_ENGINE_END

#endif // BLEND_FUNCTION_H
