SHADER version 1
@OpenGL2.Vertex
//Uniforms
uniform mat4 entitymatrix;
uniform mat4 projectioncameramatrix;

//Attributes
attribute vec3 vertex_position;
attribute vec4 vertex_color;
attribute vec2 vertex_texcoords0;

varying vec4 ex_color;
varying vec2 texcoords0;

void main ()
{	
	gl_Position = projectioncameramatrix * vec4(vertex_position, 1.0);
	ex_color.r = 1.0 - vertex_color.r;
	ex_color.g = 1.0 - vertex_color.g;
	ex_color.b = 1.0 - vertex_color.b;
	ex_color.a = vertex_color.a;
	texcoords0 = vertex_texcoords0;
}
@OpenGL2.Fragment
uniform sampler2D texture0;
varying vec4 ex_color;
varying vec2 texcoords0;

void main()
{
	gl_FragColor = ex_color * texture2D(texture0,texcoords0);
}
@OpenGLES2.Vertex
//Uniforms
uniform mat4 entitymatrix;
uniform mat4 projectioncameramatrix;

//Attributes
attribute vec3 vertex_position;
attribute vec4 vertex_color;
attribute vec2 vertex_texcoords0;

varying vec4 color;
varying vec2 texcoords0;

void main ()
{	
	gl_Position = projectioncameramatrix * vec4(vertex_position, 1.0);
	color.r = 1.0 - vertex_color.r;
	color.g = 1.0 - vertex_color.g;
	color.b = 1.0 - vertex_color.b;
	color.a = vertex_color.a;
	texcoords0 = vertex_texcoords0;
}
@OpenGLES2.Fragment
precision highp float; 

uniform sampler2D texture0;
varying vec4 color;
varying vec2 texcoords0;

void main()
{
	gl_FragColor = color * texture2D(texture0,texcoords0);
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
	//gl_FragColor.a=0.0;
}
@OpenGL4.Vertex
#version 400
#define MAX_INSTANCES 256

//Uniforms
//uniform mat4 entitymatrix;
uniform mat4 projectioncameramatrix;
uniform instancematrices { mat4 matrix[MAX_INSTANCES];} entity;

//Inputs
in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_texcoords0;

//Outputs
out vec4 ex_color;
out vec2 texcoords0;

void main ()
{	
	mat4 entitymatrix = entity.matrix[gl_InstanceID];
	gl_Position = projectioncameramatrix * vec4(vertex_position, 1.0);
	ex_color.r = 1.0 - vertex_color.r;
	ex_color.g = 1.0 - vertex_color.g;
	ex_color.b = 1.0 - vertex_color.b;
	ex_color.a = vertex_color.a;
	
	ex_color.r *= entitymatrix[0][3];
	ex_color.g *= entitymatrix[1][3];
	ex_color.b *= entitymatrix[2][3];
	ex_color.a *= entitymatrix[3][3];
	
	texcoords0 = vertex_texcoords0;
}
@OpenGL4.Fragment
#version 400

//Uniforms
uniform sampler2D texture0;
uniform vec4 materialcolordiffuse;

//Inputs
in vec4 ex_color;
in vec2 texcoords0;

//Outputs
out vec4 fragData0;

void main()
{
	fragData0 = ex_color * texture(texture0,texcoords0) * materialcolordiffuse;
}
