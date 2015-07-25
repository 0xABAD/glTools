#version 450

in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

layout (binding = 0) uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, TexCoord);
}
