SHADER version 1
@OpenGL2.Vertex
uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;

attribute vec3 vertex_position;
attribute vec2 vertex_texcoords0;

uniform vec2 position[4];
uniform vec2 texcoords[4];

varying vec2 ex_texcoords0;
varying vec4 vertexposition;

void main(void)
{
	int i = int(vertex_position.x);//gl_VertexID was implemented in GLSL 1.30, not available in 1.20.
	vertexposition = (drawmatrix * vec4(position[i], 0.0, 1.0));
	gl_Position = projectionmatrix * vertexposition;
	ex_texcoords0 = texcoords[i];
}
@OpenGL2.Fragment
uniform vec4 drawcolor;
uniform vec2 toolradius;
uniform float strength;
uniform sampler2D texture0;
uniform vec2 toolposition;
uniform vec4 mask;
uniform int slotbit;
//uniform int slot;
uniform int channel;

varying vec2 ex_texcoords0;
varying vec4 vertexposition;

//Test for a single bitwise flag between 1 and 128
bool BitwiseAnd(in int flag, in int value)
{
	for (int i=128; i>0; i/=2)
	{		
		if (value<flag) return false;
		if (i==flag)
		{
			if (value>=flag) return true;
		}
		if (value>=i) value-=i;
	}
	return false;
}

int SetTrueAndRemoveAbove(in int flag, in int value)
{
	for (int i=128; i>0; i/=2)
	{		
		if (value<flag) return value+flag;
		if (i==flag)
		{
			if (value>=flag) return value;
			return value+flag;
		}
		if (value>=i) value-=i;
	}
	return 0;
}

//Add flag to value if not already included
int BitwiseOr(in int flag, in int value)
{
	if (!BitwiseAnd(flag,value)) value += flag;
	return value;
}

//Removoe flag to value if  already included
int BitwiseOrNot(in int flag, in int value)
{
	if (BitwiseAnd(flag,value)) value -= flag;
	return value;
}

void main(void)
{
	/*
	vec4 current = texture2D(texture0,ex_texcoords0);
	float d = length(vertexposition.xy-toolposition);
	//current = current * mask;
	float alpha = current[0];//+current[1]+current[2]+current[3];
	if (d<toolradius[1])
	{
		int value = int(alpha*255.0+0.5);
		if (strength>0.0)
		{
			value = SetTrueAndRemoveAbove(slotbit,value);
			if (channel<3) current[3]=0.0;
			if (channel<2) current[2]=0.0;
			if (channel<1) current[1]=0.0;
		}
		else
		{
			value = BitwiseOrNot(slotbit,value);
		}
		alpha = float(value)/255.0;
	}
	gl_FragData[0] = current * (vec4(1.0)-mask) + mask*alpha;
	gl_FragData[0].r = alpha;
	*/
	vec4 current = texture2D(texture0,ex_texcoords0);
	float d = length(vertexposition.xy-toolposition);
	if (toolradius[1]-toolradius[0]>0.0)
	{
		d = 1.0 - (d - toolradius[0]) /(toolradius[1]-toolradius[0]);
	}
	else
	{
		d = 1.0 - (d - toolradius[0]);
	}
	d = clamp(d,0.0,1.0);
	d *= 0.2 * strength;
	gl_FragData[0] = current + mask * d;
	
}
@OpenGLES2.Vertex
uniform mediump mat4 projectionmatrix;
uniform highp mat4 drawmatrix;
uniform mediump vec2 offset;

attribute mediump vec4 vertex_position;
attribute mediump vec4 vertex_color;
attribute mediump vec2 vertex_texcoords0;
attribute mediump vec2 vertex_texcoords1;
attribute mediump vec3 vertex_normal;
 
void main(void)
{
	gl_Position = projectionmatrix * (drawmatrix * vertex_position + vec4(offset.x,offset.y,0.0,0.0));
}
@OpenGLES2.Fragment
uniform mediump vec4 drawcolor;

void main(void)
{
    gl_FragData[0] = drawcolor;
}
@OpenGL4.Vertex
#version 400

uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;
uniform float resolution;
uniform vec2 position[4];
uniform vec2 texcoords[4];

in vec3 vertex_position;
in vec2 vertex_texcoords0;

out vec2 ex_texcoords0;
out vec4 vertexposition;

void main(void)
{
	vertexposition = drawmatrix * vec4(position[gl_VertexID], 0.0, 1.0);
	gl_Position = projectionmatrix * vertexposition;
	ex_texcoords0 = texcoords[gl_VertexID];
}
@OpenGL4.Fragment
#version 400

uniform vec4 drawcolor;
uniform vec2 toolradius;
uniform float strength;
uniform sampler2D texture0;
uniform vec2 toolposition;
uniform vec4 mask;

in vec2 ex_texcoords0;
in vec4 vertexposition;

out vec4 fragData0;

void main(void)
{
	vec4 current = texture2D(texture0,ex_texcoords0);
	float d = length(vertexposition.xy-toolposition);
	if (toolradius[1]-toolradius[0]>0.0)
	{
		d = 1.0 - (d - toolradius[0]) /(toolradius[1]-toolradius[0]);
	}
	else
	{
		d = 1.0 - (d - toolradius[0]);
	}
	d = clamp(d,0.0,1.0);
	d *= 0.2 * strength;
	fragData0 = current + d * mask;
}

/*
#version 400

uniform vec4 drawcolor;
uniform vec2 toolradius;
uniform float strength;
uniform sampler2D texture0;
uniform vec2 toolposition;
uniform vec4 mask;
uniform int slotbit;
//uniform int slot;
uniform int channel;

in vec2 ex_texcoords0;
in vec4 vertexposition;

out vec4 fragData0;

void main(void)
{
	vec4 current = texture(texture0,ex_texcoords0);
	float d = length(vertexposition.xy-toolposition);
	if (toolradius[1]-toolradius[0]>0.0)
	{
		d = 1.0 - (d - toolradius[0]) /(toolradius[1]-toolradius[0]);
	}
	else
	{
		d = 1.0 - (d - toolradius[0]);
	}
	d = clamp(d,0.0,1.0);
	d *= 0.2 * strength;
	fragData0 = current + mask * d;
}
*/
