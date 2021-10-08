#version 330 core

// Interpolated values from the vertex shaders
in vec2 v_textureCoords;

// Ouput data
out vec4 color;

uniform vec4 u_DarkColor;
uniform vec4 u_LightColor;
uniform bool u_Colored;
uniform bool u_Textured;
uniform sampler2D u_Texture;

void main(){

	if (u_Textured == true) {
		vec4 textureColor = texture(u_Texture, v_textureCoords);
		color = textureColor;	
	}
	else {	
		if (u_Colored == true) {
			color = u_DarkColor;
		}
		else {
			color = u_LightColor;
		}
	}
}