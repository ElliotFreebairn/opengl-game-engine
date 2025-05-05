#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
  "}";



void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

  float vertices[] = { // Y-axis points up in the up-direction and (0,0) is the center
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  /* Copies vertices into bound buffer. args[1] = specifies size of data in bytes to pass,
   * args[2] = the actual data to send, args[2] = How we want the graphics card to manage data
   * GL_STATIC_DRAW = the data is set only once and used many times, can use DYNAMIC_DRAW 
   * for varying data (allows for faster writes)*/
 // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /*OpenGL dynamically compiles shaders at run-time from source cord*/
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  /* args[1] = how many strings passing to source code, args[2] = source code */
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
      << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
      << std::endl;
  }

  /* Shader program is the final linked version of multiple shaders combined */
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram(); // Creates a program and return and ID reference
  
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog 
      << std::endl;
  }


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
  
  /* The VBO which the vertex attrib takes is determined which VBO assigned to
    * GL_ARRAY_BUFFER, when calling glVertexAttribPointer */

  /* 0. copy vertices array in a buffer for OpenGL to use */
  glBindBuffer(GL_ARRAY_BUFFER, VBO); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  /* 1. set the vertex attrib pointers */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void*)0);
  glEnableVertexAttribArray(0);
  /* 2. use shader program to render an object */
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  
  while(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
