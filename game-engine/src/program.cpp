#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct object 
{
  unsigned int VAO;
  std::string name;

  void draw() {

  }
};

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

  while (!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window); // swaps the colour buffer, used to render and show output
    glfwPollEvents(); // checks if any events are triggered (keyboard or mousemovement), calls functions via callback methods
  }


  return 0;
}

// resizes viewport when user resizes the glfw window
void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void init_triangle(object* triangle)
{
  float vertices[] = {
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f, 0.0f
  };

  unsigned int VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

}





