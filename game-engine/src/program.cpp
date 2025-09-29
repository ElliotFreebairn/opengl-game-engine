#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "shader.h"
#include "rectangle.h"
#include "camera.h"
#include "player.h"

#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <random>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;
float pitch = 0, yaw = -90.f;

std::default_random_engine gen(static_cast<unsigned>(glfwGetTime()));
std::uniform_real_distribution<float> distribution(-2.0f, 2.0f);

void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Game game;
// Player camera
// Player current_player;
// Camera &camera = current_player.get_camera();
// std::vector<Rectangle> blocks;
// void place_block();
// Rectangle shoot_block(std::string shader_name, std::string texture_name);
// glm::vec3 shooting_velocity(0.0f);
// float last_block_place = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW Window failed to create" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Initialize GLAD - deals  with function pointers for opengl */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed to initialise" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	game.Init();

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods

		game.ProcessInput(deltaTime);
		game.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		game.Render();
		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set WindowShouldClose to true
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			game.keys[key] = true;
		else if(action == GLFW_RELEASE)
		{
			game.keys[key] = false;
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button >= 0 && button < 1024) {
        if (action == GLFW_PRESS)
            game.keys[button] = true;
        else if (action == GLFW_RELEASE)
            game.keys[button] = false;
    }
}


void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	game.ProcessMouseInput(xoffset, yoffset);
}

// resizes viewport when user resizes the glfw window
void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}