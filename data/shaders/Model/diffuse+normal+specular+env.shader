SHADER version 1
@OpenGL2.Vertex
#version 120

//Uniforms
uniform mat4 entitymatrix;
uniform vec4 materialcolordiffuse;
uniform mat4 cameramatrix;
uniform mat4 camerainversematrix;
uniform mat4 projectioncameramatrix;

//Attributes
attribute vec3 vertex_position;
attribute vec4 vertex_color;
attribute vec2 vertex_texcoords0;
attribute vec2 vertex_texcoords1;
attribute vec3 vertex_normal;
attribute vec3 vertex_tangent;
attribute vec3 vertex_binormal;

//Outputs
varying vec4 ex_vertexposition;
varying vec4 ex_color;
varying vec2 ex_texcoords0;
varying vec2 ex_texcoords1;
varying float ex_selectionstate;
varying vec3 ex_normal;
varying vec3 ex_tangent;
varying vec3 ex_binormal;

void main()
{
	mat4 entitymatrix_=entitymatrix;
	entitymatrix_[0][3]=0.0;
	entitymatrix_[1][3]=0.0;
	entitymatrix_[2][3]=0.0;
	entitymatrix_[3][3]=1.0;
	
	ex_vertexposition = entitymatrix_ * vec4(vertex_position, 1.0);
	gl_Position = projectioncameramatrix * ex_vertexposition;
	
	ex_texcoords0 = vertex_texcoords0;
	ex_texcoords1 = vertex_texcoords1;
	
	ex_color = vec4(entitymatrix[0][3],entitymatrix[1][3],entitymatrix[2][3],entitymatrix[3][3]);
	
	//If an object is selected, 10 is subtracted from the alpha color.
	//This is a bit of a hack that packs a per-object boolean into the alpha value.
	ex_selectionstate = 0.0;
	if (ex_color.a<-5.0)
	{
		ex_color.a += 10.0;
		ex_selectionstate = 1.0;
	}
	ex_color *= vec4(1.0-vertex_color.r,1.0-vertex_color.g,1.0-vertex_color.b,vertex_color.a) * materialcolordiffuse;
	
	//Transform vectors from local to global space
	mat3 nmat = mat3(camerainversematrix) * mat3(entitymatrix);
	ex_normal = normalize(nmat * vertex_normal);	
	ex_tangent = normalize(nmat * vertex_tangent);
	ex_binormal = normalize(nmat * vertex_binormal);
}
@OpenGL2.Fragment
#version 120

//Uniforms	
uniform sampler2D texture0;//diffuse map
uniform sampler2D texture1;//normal map
uniform sampler2D texture2;//specular map
uniform sampler2D texture3;//light map
uniform sampler2D texture4;//light vector map
uniform samplerCube texture5;//cube map
uniform mat4 cameramatrix;
uniform mat4 projectioncameramatrix;
uniform vec2 camerarange;
uniform float camerazoom;
uniform vec2 buffersize;
uniform mat4 camerainversematrix;
uniform vec4 ambientlight;

//Inputs
varying vec4 ex_vertexposition;
varying vec2 ex_texcoords0;
varying vec2 ex_texcoords1;
varying vec4 ex_color;
varying float ex_selectionstate;
varying vec3 ex_normal;
varying vec3 ex_tangent;
varying vec3 ex_binormal;
uniform vec3 cameraposition;
uniform mat3 cameranormalmatrix;

float DepthToZPosition(in float depth) {
	return camerarange.x / (camerarange.y - depth * (camerarange.y - camerarange.x)) * camerarange.y;
}

void main(void)
{
	vec4 outcolor = ex_color;
	float alpha;

	//Modulate blend with diffuse map
	outcolor *= texture2D(texture0,ex_texcoords0);
	alpha = outcolor.a;

	//Mod2X blend with light map
	vec4 lighting_diffuse = texture2D(texture3,ex_texcoords1) * 2.0;
	lighting_diffuse.a = 1.0;
	
	//Average light direction vector
	vec4 lightvec = texture2D(texture4,ex_texcoords1);
	vec3 lightdir = (lightvec.xyz * 2.0 - 1.0) * lightvec.a + -ex_normal * (1.0 - lightvec.a);
	lightdir = mat3(camerainversematrix) * lightdir;
	lightdir = normalize(lightdir);
	
	//Normal map
	vec3 normal = ex_normal;
	normal = normalize(texture2D(texture1,ex_texcoords0).xyz * 2.0 - 1.0);
	normal = ex_tangent * normal.x + ex_binormal * normal.y + ex_normal * normal.z;	
	
	//Lighting
	float attenuation = clamp(dot(normal,-lightdir),0.0,1.0);
	
	//Specular reflection
	vec3 screencoord = vec3(((gl_FragCoord.x/buffersize.x)-0.5) * 2.0 * (buffersize.x/buffersize.y),((-gl_FragCoord.y/buffersize.y)+0.5) * 2.0,DepthToZPosition( gl_FragCoord.z ));
	screencoord.x *= screencoord.z / camerazoom;
	screencoord.y *= -screencoord.z / camerazoom; 
	vec3 lightreflection = normalize(reflect(lightdir,normal));
	vec4 lighting_specular = vec4( pow(clamp(-dot(lightreflection,normalize(screencoord)),0.0,1.0),20.0) );
	lighting_specular *= texture2D(texture2,ex_texcoords0) * attenuation * lighting_diffuse;
	
	//Final lighting calculation
	outcolor = outcolor * ambientlight + outcolor * attenuation * lighting_diffuse;
	
	//Cubemap
	vec3 cubecoord = normalize( ex_vertexposition.xyz - cameraposition );
	normal = cameranormalmatrix * normal;
	normal.y *= -1.0;
	cubecoord = reflect(normal,cubecoord);
	outcolor += textureCube(texture5,cubecoord) * texture2D(texture2,ex_texcoords0);
	
	//Blend with selection color if selected
	gl_FragColor = outcolor * (1.0-ex_selectionstate) + ex_selectionstate * (outcolor*0.5+vec4(0.5,0.0,0.0,0.0));
	//gl_FragColor.r = cameraposition.x;
}
@OpenGLES2.Vertex
precision highp float;

//Uniforms
uniform mat4 entitymatrix;
uniform vec4 materialcolordiffuse;
uniform mat4 cameramatrix;
uniform mat4 camerainversematrix;
uniform mat4 projectioncameramatrix;

//Attributes
attribute vec3 vertex_position;
attribute vec4 vertex_color;
attribute vec2 vertex_texcoords0;
attribute vec2 vertex_texcoords1;
attribute vec3 vertex_normal;
attribute vec3 vertex_tangent;
attribute vec3 vertex_binormal;

//Outputs
varying vec4 ex_vertexposition;
varying vec4 ex_color;
varying vec2 ex_texcoords0;
varying vec2 ex_texcoords1;
varying float ex_selectionstate;
varying vec3 ex_normal;
varying vec3 ex_tangent;
varying vec3 ex_binormal;

void main()
{
	mat4 entitymatrix_=entitymatrix;
	entitymatrix_[0][3]=0.0;
	entitymatrix_[1][3]=0.0;
	entitymatrix_[2][3]=0.0;
	entitymatrix_[3][3]=1.0;
	
	ex_vertexposition = entitymatrix_ * vec4(vertex_position, 1.0);
	gl_Position = projectioncameramatrix * ex_vertexposition;
	
	ex_texcoords0 = vertex_texcoords0;
	ex_texcoords1 = vertex_texcoords1;
	
	ex_color = vec4(entitymatrix[0][3],entitymatrix[1][3],entitymatrix[2][3],entitymatrix[3][3]);
	
	//If an object is selected, 10 is subtracted from the alpha color.
	//This is a bit of a hack that packs a per-object boolean into the alpha value.
	ex_selectionstate = 0.0;
	if (ex_color.a<-5.0)
	{
		ex_color.a += 10.0;
		ex_selectionstate = 1.0;
	}
	ex_color *= vec4(1.0-vertex_color.r,1.0-vertex_color.g,1.0-vertex_color.b,vertex_color.a) * materialcolordiffuse;
	
	//Transform vectors from local to global space
	mat3 nmat = mat3(camerainversematrix) * mat3(entitymatrix);
	ex_normal = normalize(nmat * vertex_normal);	
	ex_tangent = normalize(nmat * vertex_tangent);
	ex_binormal = normalize(nmat * vertex_binormal);
}
@OpenGLES2.Fragment
precision highp float;

//Uniforms	
uniform sampler2D texture0;//diffuse map
uniform sampler2D texture1;//normal map
uniform sampler2D texture2;//specular map
uniform sampler2D texture3;//light map
uniform sampler2D texture4;//light vector map
uniform samplerCube texture5;//cube map
uniform mat4 cameramatrix;
uniform mat4 projectioncameramatrix;
uniform vec2 camerarange;
uniform float camerazoom;
uniform vec2 buffersize;
uniform mat4 camerainversematrix;
uniform vec4 ambientlight;

//Inputs
varying vec4 ex_vertexposition;
varying vec2 ex_texcoords0;
varying vec2 ex_texcoords1;
varying vec4 ex_color;
varying float ex_selectionstate;
varying vec3 ex_normal;
varying vec3 ex_tangent;
varying vec3 ex_binormal;
uniform vec3 cameraposition;
uniform mat3 cameranormalmatrix;

float DepthToZPosition(in float depth) {
	return camerarange.x / (camerarange.y - depth * (camerarange.y - camerarange.x)) * camerarange.y;
}

void main(void)
{
	vec4 outcolor = ex_color;
	float alpha;

	//Modulate blend with diffuse map
	outcolor *= texture2D(texture0,ex_texcoords0);
	alpha = outcolor.a;

	//Mod2X blend with light map
	vec4 lighting_diffuse = texture2D(texture3,ex_texcoords1) * 2.0;
	lighting_diffuse.a = 1.0;
	
	//Average light direction vector
	vec4 lightvec = texture2D(texture4,ex_texcoords1);
	vec3 lightdir = (lightvec.xyz * 2.0 - 1.0) * lightvec.a + -ex_normal * (1.0 - lightvec.a);
	lightdir = mat3(camerainversematrix) * lightdir;
	lightdir = normalize(lightdir);
	
	//Normal map
	vec3 normal = ex_normal;
	normal = normalize(texture2D(texture1,ex_texcoords0).xyz * 2.0 - 1.0);
	normal = ex_tangent * normal.x + ex_binormal * normal.y + ex_normal * normal.z;	
	
	//Lighting
	float attenuation = clamp(dot(normal,-lightdir),0.0,1.0);
	
	//Specular reflection
	vec3 screencoord = vec3(((gl_FragCoord.x/buffersize.x)-0.5) * 2.0 * (buffersize.x/buffersize.y),((-gl_FragCoord.y/buffersize.y)+0.5) * 2.0,DepthToZPosition( gl_FragCoord.z ));
	screencoord.x *= screencoord.z / camerazoom;
	screencoord.y *= -screencoord.z / camerazoom; 
	vec3 lightreflection = normalize(reflect(lightdir,normal));
	vec4 lighting_specular = vec4( pow(clamp(-dot(lightreflection,normalize(screencoord)),0.0,1.0),20.0) );
	lighting_specular *= texture2D(texture2,ex_texcoords0) * attenuation * lighting_diffuse;
	
	//Final lighting calculation
	outcolor = outcolor * ambientlight + outcolor * attenuation * lighting_diffuse;
	
	//Cubemap
	vec3 cubecoord = normalize( ex_vertexposition.xyz - cameraposition );
	normal = cameranormalmatrix * normal;
	normal.y *= -1.0;
	cubecoord = reflect(normal,cubecoord);
	outcolor += textureCube(texture5,cubecoord) * texture2D(texture2,ex_texcoords0);
	
	//Blend with selection color if selected
	gl_FragColor = outcolor * (1.0-ex_selectionstate) + ex_selectionstate * (outcolor*0.5+vec4(0.5,0.0,0.0,0.0));
	//gl_FragColor.r = cameraposition.x;
}
@OpenGL4.Vertex
#version 400
#define MAX_INSTANCES 256

//Uniforms
uniform vec4 materialcolordiffuse;
uniform mat4 cameramatrix;
uniform mat4 camerainversematrix;
uniform mat4 projectioncameramatrix;
uniform instancematrices { mat4 matrix[MAX_INSTANCES];} entity;

//Attributes
in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_texcoords0;
in vec2 vertex_texcoords1;
in vec3 vertex_normal;
in vec3 vertex_tangent;
in vec3 vertex_binormal;

//Outputs
out vec4 ex_vertexposition;
out vec4 ex_color;
out vec2 ex_texcoords0;
out vec2 ex_texcoords1;
out float ex_selectionstate;
out vec3 ex_normal;
out vec3 ex_tangent;
out vec3 ex_binormal;

void main()
{
	mat4 entitymatrix = entity.matrix[gl_InstanceID];
	mat4 entitymatrix_=entitymatrix;
	entitymatrix_[0][3]=0.0;
	entitymatrix_[1][3]=0.0;
	entitymatrix_[2][3]=0.0;
	entitymatrix_[3][3]=1.0;
	
	ex_vertexposition = entitymatrix_ * vec4(vertex_position, 1.0);
	gl_Position = projectioncameramatrix * ex_vertexposition;
	
	ex_texcoords0 = vertex_texcoords0;
	ex_texcoords1 = vertex_texcoords1;
	
	ex_color = vec4(entitymatrix[0][3],entitymatrix[1][3],entitymatrix[2][3],entitymatrix[3][3]);
	
	//If an object is selected, 10 is subtracted from the alpha color.
	//This is a bit of a hack that packs a per-object boolean into the alpha value.
	ex_selectionstate = 0.0;
	if (ex_color.a<-5.0)
	{
		ex_color.a += 10.0;
		ex_selectionstate = 1.0;
	}
	ex_color *= vec4(1.0-vertex_color.r,1.0-vertex_color.g,1.0-vertex_color.b,vertex_color.a) * materialcolordiffuse;
	
	//Transform vectors from local to global space
	mat3 nmat = mat3(camerainversematrix) * mat3(entitymatrix);
	ex_normal = normalize(nmat * vertex_normal);	
	ex_tangent = normalize(nmat * vertex_tangent);
	ex_binormal = normalize(nmat * vertex_binormal);
}
@OpenGL4.Fragment
#version 400
#define BFN_ENABLED 1

//Uniforms	
uniform sampler2D texture0;//diffuse map
uniform sampler2D texture1;//normal map
uniform sampler2D texture2;//specular map
uniform samplerCube texture5;//cube map
uniform samplerCube texture15;//BFN map
uniform mat4 cameramatrix;
uniform mat4 projectioncameramatrix;
uniform vec2 camerarange;
uniform float camerazoom;
uniform vec2 buffersize;
uniform mat4 camerainversematrix;
uniform vec4 ambientlight;
uniform vec4 materialcolorspecular;
uniform mat3 cameranormalmatrix;
uniform vec3 cameraposition;

//Inputs
in vec4 ex_vertexposition;
in vec2 ex_texcoords0;
in vec2 ex_texcoords1;
in vec4 ex_color;
in float ex_selectionstate;
in vec3 ex_normal;
in vec3 ex_tangent;
in vec3 ex_binormal;

out vec4 fragData0;
out vec4 fragData1;
out vec4 fragData2;
out vec4 fragData3;

float DepthToZPosition(in float depth) {
	return camerarange.x / (camerarange.y - depth * (camerarange.y - camerarange.x)) * camerarange.y;
}

void main(void)
{
	vec4 outcolor = ex_color;
	float alpha;

	//Modulate blend with diffuse map
	outcolor *= texture(texture0,ex_texcoords0);
	alpha = outcolor.a;
	
	//Normal map
	vec3 normal = ex_normal;
	normal = normalize(texture(texture1,ex_texcoords0).xyz * 2.0 - 1.0);
	float ao = normal.z;
	normal = ex_tangent * normal.x + ex_binormal * normal.y + ex_normal * normal.z;	
	
	//Cubemap
	vec3 cubecoord = normalize( ex_vertexposition.xyz - cameraposition );
	vec3 reflectdir = cameranormalmatrix * normal;
	reflectdir.y *= -1.0;
	cubecoord = reflect(reflectdir,cubecoord);
	
	vec4 emission = texture(texture5,cubecoord) * texture(texture2,ex_texcoords0);
	
	//Blend with selection color if selected
	fragData0 = outcolor;// * (1.0-ex_selectionstate) + ex_selectionstate * (outcolor*0.5+vec4(0.5,0.0,0.0,0.0));
#if BFN_ENABLED==1
	//Best-fit normals
	fragData1 = texture(texture15,normalize(vec3(normal.x,-normal.y,normal.z)));
	fragData1.a = fragData0.a;
#else
	//Low-res normals
	fragData1 = vec4(normalize(normal)*0.5+0.5,fragData0.a);
#endif
	fragData1.a = materialcolorspecular.r * 0.299 + materialcolorspecular.g * 0.587 + materialcolorspecular.b * 0.114;
	int materialflags=1;
	if (ex_selectionstate>0.0) materialflags += 2;
	fragData2 = vec4(0.0,0.0,0.0,materialflags/255.0);
}
