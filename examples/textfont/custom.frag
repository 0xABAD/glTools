#version 450

in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

layout (binding = 0) uniform sampler2D Bitmap;

uniform vec4 TextColor;
uniform vec4 BackgroundTextColor;

void main()
{
	vec4 texel = texture(Bitmap, TexCoord);

	if (texel.r == 0.0f)
		FragColor = BackgroundTextColor;
	else
		FragColor = TextColor;
}
