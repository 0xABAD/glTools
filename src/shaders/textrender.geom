#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in float Width[];
in float Height[];
in float Index[];

out vec2 TexCoord;

uniform mat4  MVP;
uniform float StartIndex;	// Index of first character in bitmap
uniform float ImageWidth;
uniform float CellWidth;
uniform float CellHeight;
uniform float CellCountX;	// ImageWidth / CellWidth
uniform float ImgY;			// CellHeight / ImageHeight

void main()
{
	vec4  pt 	= gl_in[0].gl_Position;
	float scale  = Height[0] / CellHeight;
	float width  = Width[0] * scale;		  	  // Proportion with Height
	float ImgX   = Width[0] / ImageWidth;		  // Width in texture coordinates
	float offset = Index[0] - StartIndex;
	float row 	 = floor(offset / CellCountX);
	float col    = float(int(offset) % int(CellCountX));
	float s 	 = col * CellWidth / ImageWidth;
	float t      = (1.0 - row * ImgY) - ImgY;

	gl_Position = MVP * pt;
	TexCoord    = vec2(s, t);
	EmitVertex();

	gl_Position = MVP * vec4(pt.x + width, pt.y, pt.z, 1.0);
	TexCoord    = vec2(s + ImgX, t);
	EmitVertex();
	
	gl_Position = MVP * vec4(pt.x, pt.y + Height[0], pt.z, 1.0);
	TexCoord    = vec2(s, t + ImgY);
	EmitVertex();
	
	gl_Position = MVP * vec4(pt.x + width, pt.y + Height[0], pt.z, 1.0);
	TexCoord    = vec2(s + ImgX, t + ImgY);
	EmitVertex();
	
	EndPrimitive();
}
