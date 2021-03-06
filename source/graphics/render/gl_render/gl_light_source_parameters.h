#ifndef LIGHT_SOURCE_PARAMETERS_H
#define LIGHT_SOURCE_PARAMETERS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    struct LightSourceShaderParameters
    {
        unsigned enabled;
        unsigned direction;
        unsigned position;
        unsigned view_direction;
        unsigned view_position;
        unsigned diffuse_color;
        unsigned specular_color;
        unsigned ambient_color;
        unsigned attenuation_constant;
        unsigned attenuation_linear;
        unsigned attenuation_quadric;
        unsigned spot;
        unsigned type;
        unsigned attenuation_model;
    };
}
PUNK_ENGINE_END

#endif // LIGHT_SOURCE_PARAMETERS_H
