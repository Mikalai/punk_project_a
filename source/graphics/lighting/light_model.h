#ifndef LIGHT_MODEL_H
#define LIGHT_MODEL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics
{
	enum class LightModel {
		PerVertexDiffuse,
		PerFragmentDiffuse,
        BumpMappingDiffuse
	};

	enum class LightAttenuation {
		Constant,
		Linear,
		Quadratic
	};

	enum class LightType {
		Point,
        Direction,
        Spot
	};

	extern PUNK_ENGINE_API const Core::String AsString(LightModel value);
	extern PUNK_ENGINE_API const Core::String AsString(LightAttenuation  value);
	extern PUNK_ENGINE_API const Core::String AsString(LightType value);
}
PUNK_ENGINE_END

#endif // LIGHT_MODEL_H
