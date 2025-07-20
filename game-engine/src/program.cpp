#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "resource_manager.h"
#include "shader.h"
#include "rectangle.h"

#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <random>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float last_block_place = 0.0f;

float lastX = 400, lastY = 300;
float pitch = 0, yaw = -90.f;

bool firstMouse = true;

std::default_random_engine gen(static_cast<unsigned>(glfwGetTime()));
std::uniform_real_distribution<float> distribution(-2.0f, 2.0f);

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

void place_block();

std::vector<Rectangle> blocks;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use opengl core, access subset of features

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine", NULL, NULL);
  if (window == NULL)
  {
    std:: cout << "GLFW Window failed to create" << std::endl;
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


  //srand (static_cast<unsigned>(time(0))); // seeding the random number generator

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);
    
    glm::mat4 view = glm::mat4(1.0f);
    view =  glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    shader.SetMatrix4("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.SetMatrix4("projection", projection);

    for (Rectangle& block : blocks) {
      block.draw();
    }
    glfwSwapBuffers(window);
  }

  ResourceManager::Clear();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void place_block() {
  Rectangle block("rectangle", "block");

  // Position a ceratin distance in front of the player
  glm::vec3 target = cameraPos + glm::normalize(cameraFront) * 5.0f;

  glm::vec3 block_pos = glm::floor(target);
  
  block.Position = block_pos;
 // float x = distribution(gen);
 // float y = distribution(gen);
 // float z = distribution(gen);

  //std::cout << "output of distribution gen: " << std::to_string(distribution(gen)) << "size of blocks vector: " << blocks.size() << "x: " << x << " y: " << y << " z: " << z << std::endl;

  //glm::vec3 translation(x, y, z);
  //block.Position = translation;

  //block.set_model_translation(translation);
  blocks.push_back(block);
}

// resizes viewport when user resizes the glfw window
void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  const float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraUp;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraUp;

  float current_frame = glfwGetTime();
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    if (current_frame - last_block_place >= 0.2f) {
      last_block_place = current_frame;
      place_block();
      std::cout << "last x pos: " << lastX  << " last y pos: " << lastY << std::endl;
    }
  }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed: y ranges bottom to top
  lastX = xpos;
  lastY = ypos;

  const float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}
