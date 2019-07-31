// NOTE: before proceeding further, it is recommended you learn about the programmable graphics pipeline.
// To know more about the programmable graphics pipeline please visit this website:
// http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-1:-The-Graphics-Pipeline.html

// The vertex shader is used to transform the attributes of vertices such as color, texture, position
// and the direction from the original color space to the display space. It allows the original objects
// to be distorted or reshaped in any manner


#version 430
// Vertex attribute for position, which is at location 0
layout (location=0) in vec3 position;


layout (location=2) uniform mat4 worldMatrix;


void main()
{
 // gl_Position is inbuilt vertex shader output variable of type vec4.
	
	gl_Position  = worldMatrix * vec4(position,1);
}
