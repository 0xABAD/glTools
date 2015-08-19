#version 450

layout (location = 0) in vec3 Point;
layout (location = 1) in vec3 Trait;

out float Width;
out float Height;
out float Index;

void main()
{
	Width  = Trait.x;
	Height = Trait.y;
	Index  = Trait.z;

	gl_Position = vec4(Point, 1.0);
}
