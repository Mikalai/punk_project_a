#ifndef FOG_MODE_H
#define FOG_MODE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics
{
	enum class FogMode { Linear, Exponent, Exponent2 };

	extern const Core::String PUNK_ENGINE_API AsString(FogMode mode);
}
PUNK_ENGINE_END

#endif // FOG_MODE_H
