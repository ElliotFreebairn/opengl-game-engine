#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine Practice", NULL, NULL);
  if(window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);


  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");

  /* ---------------- Linking Vertex Attributes ----------------- */

  /* args[0] = which vertex attrib we want to configure (layout = 0),
    * args[1] = size of the vertex attrib (vec3),
    * args[2] = type of data (GL_FLOAT = vec*)
    * args[3] = whether data to be normalized,
    * args[4] = stride, space between consecutive vertex attributes,
    * args[5] = the offset of where the position data beings in buffer */
  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
  //                      (void*)0);
  //glEnableVertexAttribArray(0);
  
  /* --------------------- Vertex Array Objects ------------------- */
  float vertices[] = {
    // positions      // colours
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,// bottom right
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f // top left
  };
  unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
  };
  


  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  /* 1. bind VAO */
  glBindVertexArray(VAO);
  /* 2. copy vertices array in buffer for OpenGL to use */
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  /* 3. then set vertex attributes pointers */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)0); 
  glEnableVertexAttribArray(0);
  /* Color attribute */
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  
  /* ------------ Uniform Shader ----------------- */


  while(!glfwWindowShouldClose(window)) 
  { 
    processInput(window);

    // render
    // clear the colourbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}


