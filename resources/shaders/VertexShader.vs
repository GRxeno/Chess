#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec2 textureColor;
// Values that stay constant for the whole mesh.
uniform mat4 u_Projection;

void main(){	

	// Output position of the vertex
	gl_Position.xyz = vertexPosition;
	gl_Position.w = 1.0;

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	textureColor = vertexColor;
}

