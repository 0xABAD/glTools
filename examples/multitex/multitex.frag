#version 450

in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

layout (binding = 0) uniform sampler2D tex1;
layout (binding = 1) uniform sampler2D tex2;

void main()
{
	vec4 color1  = texture(tex1, TexCoord);
	vec4 color2  = texture(tex2, TexCoord);

	FragColor = mix(color1, color2, 0.2);
}
