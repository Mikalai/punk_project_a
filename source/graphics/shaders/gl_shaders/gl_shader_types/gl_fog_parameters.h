#ifndef FOG_PARAMETERS_H
#define FOG_PARAMETERS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    struct FogShaderParameters
    {
        unsigned color;
        unsigned density;
        unsigned start;
        unsigned end;
        unsigned scale;
    };
}
PUNK_ENGINE_END

#endif // FOG_PARAMETERS_H
