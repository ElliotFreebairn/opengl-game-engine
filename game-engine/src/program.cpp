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

struct Rectangle3D
{
  unsigned int VAO;

   
  void draw(std::string shaderName) {
    Shader shader = ResourceManager::GetShader(shaderName);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5, 1.0f, 0.0f));
    shader.SetMatrix4("model", model);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    shader.SetMatrix4("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.SetMatrix4("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 36);
 
  }
};

void init_rectangle(Rectangle3D* obj);

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
  Rectangle3D rectangle;
  init_rectangle(&rectangle);
   
  //ResourceManager::LoadShader("shaders/vertex.vs", "shaders/fragment.fs", "triangle");
  ResourceManager::LoadShader("shaders/vertex.vs", "shaders/fragment.fs", "rectangle");

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // plain 2D projection matrix
    ResourceManager::GetShader("rectangle").Use();
    std::cout << ResourceManager::GetShader("rectangle").ID;
    
    glBindVertexArray(rectangle.VAO);
    rectangle.draw("rectangle");
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void init_rectangle(Rectangle3D* rectangle)
{
 // float vertices[] = {
 //   // first triangle
 //   0.5f, 0.5f, 0.0f, // top right
 //   0.5f, -0.5f, 0.0f, // bottom right
 //   -0.5f, -0.5f, 0.0f, // bottom left
 //   -0.5f, 0.5f, 0.0f // top left
 // };
 // unsigned int indices[] = {
 //   0, 1, 3,
 //   1, 2, 3
 // };
  
  float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
  };

  unsigned int VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  rectangle->VAO =VAO;

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // copy our index array in a element buffer for opengl to use
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);

}





