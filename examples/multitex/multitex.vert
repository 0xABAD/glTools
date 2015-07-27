#version 450

layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 TextureCoord;

out vec2 TexCoord;

uniform mat4  Translation;
uniform float TexScale;

void main()
{
	TexCoord 	= TextureCoord * TexScale;
	gl_Position = Translation * vec4(VertexPosition, 0.0, 1.0);
}