#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"

uniform mat4 uView;
uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;
uniform Light uLight[MAX_LIGHTS];

in vec3 vViewVertexNormal;
in vec3 vViewVertexPosition;
in vec2 vVertexTextureCoord0;

out vec4 vFragmentColor;

void main()
{
    int i;
    vec4 light_color = vec4(0,0,0,0);
    for (i = 0; i != MAX_LIGHTS; ++i)
    {
        if (uLight[i].enabled == 0)
            continue;

        vec3 light_position = (uView * uLight[i].position).xyz;
        vec3 object_to_light = normalize(light_position - vViewVertexPosition);

        float dst = length(light_position - vViewVertexPosition);

        float sc = 1;
        if (uLight[i].type == DIRECTION_LIGHT)
        {
            float p = uLight[i].spot;
            vec3 light_direction = normalize((uView * uLight[i].direction).xyz);
            sc = SpotAttenuation(light_direction, object_to_light, p);
        }

        float k0 = uLight[i].attenuation_constant;
        float k1 = uLight[i].attenuation_linear;
        float k2 = uLight[i].attenuation_quadric;
        int mode = uLight[i].attenuation_model;

        float c = 1;
        if (mode == ATTENUATION_CONSTANT)
            c = AttenuationConstant(k0);
        else if (mode == ATTENUATION_LINEAR)
            c = AttenuationLinear(k0, k1, dst);
        else if (mode == ATTENUATION_QUADRIC)
            c = AttenuationQuadric(k0, k1, k2, dst);

        light_color += uLight[i].ambient_color + sc * c * uLight[i].diffuse_color * max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
        //light_color += max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
    }
    vec4 diffuse_texture = texture2D(uDiffuseMap, vVertexTextureCoord0);
    vFragmentColor = light_color * uDiffuseColor * diffuse_texture;
	//vFragmentColor = vec4(1 + 0.5*vVertexTextureCoord0, 0, 1);
}
