#version 450

layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 TextureCoord;

out vec2 TexCoord;

void main()
{
	TexCoord 	= TextureCoord;
	gl_Position = vec4(VertexPosition, 0.0, 1.0);
}
