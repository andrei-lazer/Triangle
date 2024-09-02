#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;


uniform float scale;

// Outputs the color for the Fragment Shader
out vec3 color;

void main()
{
	gl_Position = vec4(aPos.x * (1.0f + scale), aPos.y * (1.0f + scale), aPos.z * (1.0f + scale), 1.0);
	color = aColor;
}
