#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 textureCoords;

// Output data ; will be interpolated for each fragment.
out vec2 v_textureCoords;
// Values that stay constant for the whole mesh.
uniform mat4 u_MVP;

void main(){	

	// Output position of the vertex
	gl_Position = u_MVP * vertexPosition;

	v_textureCoords = textureCoords;
}

