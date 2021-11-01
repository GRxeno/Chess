// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>

// Include ImGui headers
#include "API/imgui/imgui.h"
#include "API/imgui/imgui_impl_glfw.h"
#include "API/imgui/imgui_impl_opengl3.h"

// #include "gtest/gtest.h"
// #include "gmock/gmock.h"

// Include project headers
#include "Board.h"
#include "Piece.h"
#include "GameState.h"

// window variables
GLFWwindow* window;
uint32_t width = 800;

// timing variables
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// game variables
GameState* gameP;
float darkColor[4] = {255/255.0f,137/255.0f,81/255.0f,255/255.0f};
float lightColor[4] = {255/255.0f,215/255.0f,174/255.0f,255/255.0f};
double xPosCursor, yPosCursor;
int xCur, yCur, xLast, yLast;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		xLast = (int)xPosCursor / 100;
		yLast = (int)yPosCursor / 100;
	}
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		xCur = (int)xPosCursor / 100;
		yCur = (int)yPosCursor / 100;

		if (!(xLast == xCur && yLast == yCur)){
			if((xCur >= 0) && (xCur <= 7) && (yCur >= 0) && (yCur <= 7)){
				// std::cout << "PRESSED ON: " << yLast << " . " << xLast << " | RELEASED ON: " << yCur << " . " << xCur << std::endl;
				gameP->Move(yLast, xLast, yCur, xCur);
			}
		}
	}
}

int main(int argc, char* argv[])
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
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create Shader
		Shader boardShader("resources/shaders/BoardVertexShader.vs", "resources/shaders/BoardFragmentShader.fs");
		boardShader.Bind();

		Renderer renderer = Renderer();   
		
		GameState game;
		gameP = &game;

		game.PrintState();

		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

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

			
			
			boardShader.Bind();
			game.Draw(renderer, boardShader);



			// ImGui::Begin("Edit Variables");
			// ImGui::ColorEdit4("Board's Dark Color", darkColor);
			// ImGui::ColorEdit4("Board's Light Color", lightColor);
			// ImGui::SliderFloat2("Piece1's Position", piece1->getTranslation(), 0.0f, 1.75f);


			
			boardShader.SetUniform4f("u_DarkColor",darkColor[0],darkColor[1],darkColor[2],darkColor[3]);
			boardShader.SetUniform4f("u_LightColor",lightColor[0],lightColor[1],lightColor[2],lightColor[3]);

			
			// ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwGetCursorPos(window, &xPosCursor, &yPosCursor);

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

	return 1;
}