#ifndef MATERIAL_PARAMETERS_H
#define MATERIAL_PARAMETERS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    struct MaterialShaderParameters
    {
        unsigned emission;
        unsigned ambient;
        unsigned diffuse;
        unsigned specular;
        unsigned shininess;
    };
}
PUNK_ENGINE_END

#endif // MATERIAL_PARAMETERS_H
