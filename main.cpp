// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>

// Include Project Headers
#include "API/Shader.h"
#include "API/VertexBuffer.h"
#include "API/VertexArray.h"
#include "API/Renderer.h"
#include "API/Texture.h"

// Include ImGui headers
#include "API/imgui/imgui.h"
#include "API/imgui/imgui_impl_glfw.h"
#include "API/imgui/imgui_impl_opengl3.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

GLFWwindow* window;


uint32_t width = 800;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float positions[] = {         
-1.0f,-1.0f,
-0.75f,-1.0f,
-0.75f,-0.75f,
-0.75f,-0.75f,
-1.0f,-0.75f,
-1.0f,-1.0f,
-1.0f,-0.5f,
-0.75f,-0.5f,
-0.75f,-0.25f,
-0.75f,-0.25f,
-1.0f,-0.25f,
-1.0f,-0.5f,
-1.0f,0.0f,
-0.75f,0.0f,
-0.75f,0.25f,
-0.75f,0.25f,
-1.0f,0.25f,
-1.0f,0.0f,
-1.0f,0.5f,
-0.75f,0.5f,
-0.75f,0.75f,
-0.75f,0.75f,
-1.0f,0.75f,
-1.0f,0.5f,
-0.5f,-1.0f,
-0.25f,-1.0f,
-0.25f,-0.75f,
-0.25f,-0.75f,
-0.5f,-0.75f,
-0.5f,-1.0f,
-0.5f,-0.5f,
-0.25f,-0.5f,
-0.25f,-0.25f,
-0.25f,-0.25f,
-0.5f,-0.25f,
-0.5f,-0.5f,
-0.5f,0.0f,
-0.25f,0.0f,
-0.25f,0.25f,
-0.25f,0.25f,
-0.5f,0.25f,
-0.5f,0.0f,
-0.5f,0.5f,
-0.25f,0.5f,
-0.25f,0.75f,
-0.25f,0.75f,
-0.5f,0.75f,
-0.5f,0.5f,
0.0f,-1.0f,
0.25f,-1.0f,
0.25f,-0.75f,
0.25f,-0.75f,
0.0f,-0.75f,
0.0f,-1.0f,
0.0f,-0.5f,
0.25f,-0.5f,
0.25f,-0.25f,
0.25f,-0.25f,
0.0f,-0.25f,
0.0f,-0.5f,
0.0f,0.0f,
0.25f,0.0f,
0.25f,0.25f,
0.25f,0.25f,
0.0f,0.25f,
0.0f,0.0f,
0.0f,0.5f,
0.25f,0.5f,
0.25f,0.75f,
0.25f,0.75f,
0.0f,0.75f,
0.0f,0.5f,
0.5f,-1.0f,
0.75f,-1.0f,
0.75f,-0.75f,
0.75f,-0.75f,
0.5f,-0.75f,
0.5f,-1.0f,
0.5f,-0.5f,
0.75f,-0.5f,
0.75f,-0.25f,
0.75f,-0.25f,
0.5f,-0.25f,
0.5f,-0.5f,
0.5f,0.0f,
0.75f,0.0f,
0.75f,0.25f,
0.75f,0.25f,
0.5f,0.25f,
0.5f,0.0f,
0.5f,0.5f,
0.75f,0.5f,
0.75f,0.75f,
0.75f,0.75f,
0.5f,0.75f,
0.5f,0.5f,
-0.75f,-0.75f,
-0.5f,-0.75f,
-0.5f,-0.5f,
-0.5f,-0.5f,
-0.75f,-0.5f,
-0.75f,-0.75f,
-0.75f,-0.25f,
-0.5f,-0.25f,
-0.5f,0.0f,
-0.5f,0.0f,
-0.75f,0.0f,
-0.75f,-0.25f,
-0.75f,0.25f,
-0.5f,0.25f,
-0.5f,0.5f,
-0.5f,0.5f,
-0.75f,0.5f,
-0.75f,0.25f,
-0.75f,0.75f,
-0.5f,0.75f,
-0.5f,1.0f,
-0.5f,1.0f,
-0.75f,1.0f,
-0.75f,0.75f,
-0.25f,-0.75f,
0.0f,-0.75f,
0.0f,-0.5f,
0.0f,-0.5f,
-0.25f,-0.5f,
-0.25f,-0.75f,
-0.25f,-0.25f,
0.0f,-0.25f,
0.0f,0.0f,
0.0f,0.0f,
-0.25f,0.0f,
-0.25f,-0.25f,
-0.25f,0.25f,
0.0f,0.25f,
0.0f,0.5f,
0.0f,0.5f,
-0.25f,0.5f,
-0.25f,0.25f,
-0.25f,0.75f,
0.0f,0.75f,
0.0f,1.0f,
0.0f,1.0f,
-0.25f,1.0f,
-0.25f,0.75f,
0.25f,-0.75f,
0.5f,-0.75f,
0.5f,-0.5f,
0.5f,-0.5f,
0.25f,-0.5f,
0.25f,-0.75f,
0.25f,-0.25f,
0.5f,-0.25f,
0.5f,0.0f,
0.5f,0.0f,
0.25f,0.0f,
0.25f,-0.25f,
0.25f,0.25f,
0.5f,0.25f,
0.5f,0.5f,
0.5f,0.5f,
0.25f,0.5f,
0.25f,0.25f,
0.25f,0.75f,
0.5f,0.75f,
0.5f,1.0f,
0.5f,1.0f,
0.25f,1.0f,
0.25f,0.75f,
0.75f,-0.75f,
1.0f,-0.75f,
1.0f,-0.5f,
1.0f,-0.5f,
0.75f,-0.5f,
0.75f,-0.75f,
0.75f,-0.25f,
1.0f,-0.25f,
1.0f,0.0f,
1.0f,0.0f,
0.75f,0.0f,
0.75f,-0.25f,
0.75f,0.25f,
1.0f,0.25f,
1.0f,0.5f,
1.0f,0.5f,
0.75f,0.5f,
0.75f,0.25f,
0.75f,0.75f,
1.0f,0.75f,
1.0f,1.0f,
1.0f,1.0f,
0.75f,1.0f,
0.75f,0.75f,
};

float darkColor[4] = {0.25f,0.25f,0.25f,1.0f};
float lightColor[4] = {0.8f,0.8f,0.8f,1.0f};

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
}




int main(void)
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, width, "Chess", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glfwSwapInterval(1); // V-sync

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	{
		// Create Shader
		Shader shader("resources/shaders/VertexShader.vs", "resources/shaders/FragmentShader.fs");
		shader.Bind();
 
		// glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 400.0f);
		// shader.SetUniformMatrix4f("u_Projection", Projection);

		VertexBufferLayout layout; 
		layout.Push(2);
 
		VertexArray va;
		VertexBuffer vb = VertexBuffer(positions, sizeof(positions));
		va.AddBuffer(vb, layout, 0);

		Texture texture("resources/textures/Chess_rlt60.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		Renderer renderer = Renderer();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void) io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		while (!glfwWindowShouldClose(window))
		{
			
			// per-frame time logic
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// keyboard input
			processInput(window);

			// Clear the screen.
			renderer.ClearScreen();

			// ImGui
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			
			renderer.Draw(va, shader);
			shader.SetUniform4f("u_Color",darkColor[0],darkColor[1],darkColor[2],darkColor[3]);
			// background
			glClearColor(lightColor[0],lightColor[1],lightColor[2],lightColor[3]);


			ImGui::Begin("Edit Variables");
			ImGui::ColorEdit4("Board's Dark Color", darkColor);
			ImGui::ColorEdit4("Board's Light Color", lightColor);

			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();

		} 
	}

	// Close ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}