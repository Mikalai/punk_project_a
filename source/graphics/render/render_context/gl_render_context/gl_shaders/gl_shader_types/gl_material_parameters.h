#ifndef MATERIAL_PARAMETERS_H
#define MATERIAL_PARAMETERS_H

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

#endif // MATERIAL_PARAMETERS_H
