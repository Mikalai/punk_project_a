
#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"

uniform mat3 uNormalMatrix;
uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;

uniform mat4 uBones[64];

out vec3 vViewVertexNormal;
out vec3 vViewVertexPosition;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 9) in vec4 rm_BonesId;
layout(location = 10) in vec4 rm_Weights;

void main(void)
{	
	vec4 pos =  vec4(0.0, 0.0, 0.0, 0.0);
	vec3 norm = vec3(0.0, 0.0, 0.0);
	
	vec4 b_id = rm_BonesId;
	vec4 weight = rm_Weights;
	
	for (int i = 0; i < 4; i++)
	{
			mat4 m44 = uBones[int(b_id[i])];	
			mat3 m33 = mat3(m44[0].xyz, m44[1].xyz, m44[2].xyz);		
			pos += m44 * vec4(rm_Vertex.xyz, 1.0) * weight[i];			
			norm += m33 * rm_Normal.xyz * weight[i];
	}
		
	pos = pos / pos.w;
					 
	vViewVertexPosition = (uViewWorld * pos).xyz;
	vViewVertexNormal = normalize(uNormalMatrix * norm);
	gl_Position = uProjViewWorld * pos;
}

	
