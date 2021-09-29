#version 330 core

// Interpolated values from the vertex shaders
in vec2 textureColor;

// Ouput data
out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	color = u_Color;

}