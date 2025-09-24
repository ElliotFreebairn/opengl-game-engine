#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

glm::vec3 shooting_velocity(0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float last_block_place = 0.0f;

float lastX = 400, lastY = 300;
float pitch = 0, yaw = -90.f;

bool firstMouse = true;

std::default_random_engine gen(static_cast<unsigned>(glfwGetTime()));
std::uniform_real_distribution<float> distribution(-2.0f, 2.0f);

void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

void place_block();
Rectangle shoot_block(std::string shader_name, std::string texture_name);

std::vector<Rectangle> blocks;

// Player camera
Player current_player;
Camera *camera;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use opengl core, access subset of features

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW Window failed to create" << std::endl;
		glfwTerminate(); // destorys remaining windows and cursors
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	/* Initialize GLAD - deals  with function pointers for opengl */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed to initialise" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	Shader shader = ResourceManager::LoadShader("shaders/vertex.vs", "shaders/fragment.fs", "rectangle");
	ResourceManager::LoadTexture("resources/textures/block.jpg", true, "block");

	camera = &current_player.get_camera();

	Rectangle shooting_block("rectangle", "block");
	shooting_block.set_position(camera->Position + glm::normalize(camera->Front) * 2.0f);
	shooting_velocity = glm::normalize(camera->Front) * 3.0f; // 10 units per secon


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera->Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		shader.SetMatrix4("projection", projection);

		shooting_block.Position += shooting_velocity * deltaTime;

		std::cout << "Shooting block postion: "
				  << shooting_block.Position.x << ", "
				  << shooting_block.Position.y << ", "
				  << shooting_block.Position.z << std::endl;

		glm::mat4 view = camera->GetViewMatrix();
		shader.SetMatrix4("view", view);

		shooting_block.draw();
		for (Rectangle &block : blocks)
		{
			block.draw();
		}
		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void place_block()
{
	Rectangle block("rectangle", "block");

	// Position a ceratin distance in front of the player
	glm::vec3 target = camera->Position + glm::normalize(camera->Front) * 5.0f;
	glm::vec3 block_pos = glm::floor(target);

	block.Position = block_pos;
	blocks.push_back(block);
}

Rectangle shoot_block(std::string shader_name, std::string texture_name)
{
	Rectangle block(shader_name, texture_name);

	// Position a certain distance in front of the player
	glm::vec3 target = camera->Position + glm::normalize(camera->Front) * 5.0f;
	glm::vec3 block_pos = glm::floor(target);

	block.set_position(block_pos);
	blocks.push_back(block);
	return block;
}

// resizes viewport when user resizes the glfw window
void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	float current_frame = glfwGetTime();
	current_player.process_inputs(window, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (current_frame - last_block_place >= 0.1f)
		{
			last_block_place = current_frame;
			place_block();
			std::cout << "last x pos: " << lastX << " last y pos: " << lastY << std::endl;
		}
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

	// ---------------- conflicting line, think about this one
	camera->ProcessMouseMovement(xoffset, yoffset);
}
