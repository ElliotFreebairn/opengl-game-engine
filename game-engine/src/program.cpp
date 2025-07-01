#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "resource_manager.h"
#include "shader.h"

#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Object 
{
  unsigned int VAO;
  std::string name;

  void draw() {

  }
};

void init_triangle(Object* obj);

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
  }
  glfwMakeContextCurrent(window);

  /* Initialize GLAD - deals  with function pointers for opengl */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "GLAD failed to initialise" << std::endl;
    return -1;
  }

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  Object triangle;
  init_triangle(&triangle);
  std::cout << triangle.VAO;
   
  ResourceManager::LoadShader("shaders/vertex.vs", "shaders/fragment.fs", "triangle");

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // plain 2D projection matrix
    ResourceManager::GetShader("triangle").Use();
    std::cout << ResourceManager::GetShader("triangle").ID;
    
    glBindVertexArray(triangle.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }

  return 0;
}

// resizes viewport when user resizes the glfw window
void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void init_triangle(Object* triangle)
{
  float vertices[] = {
    // first triangle
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f // top left
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int VBO, VAO, EBO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  triangle->VAO =VAO;

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // copy our index array in a element buffer for opengl to use
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);

}





